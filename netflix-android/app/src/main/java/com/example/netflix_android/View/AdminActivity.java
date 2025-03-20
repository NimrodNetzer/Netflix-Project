package com.example.netflix_android.View;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import com.example.netflix_android.Adapters.AdminCategoryAdapter;
import com.example.netflix_android.ViewModel.CategoryViewModel;
import com.example.netflix_android.ViewModel.CategoryViewModelFactory;
import com.google.android.material.button.MaterialButton;
import com.google.android.material.button.MaterialButtonToggleGroup;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.example.netflix_android.Adapters.CategoryAdapter;
import com.example.netflix_android.Adapters.MoviesAdapter;
import com.example.netflix_android.Entities.Category;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.R;
import com.example.netflix_android.Repository.CategoryRepository;
import com.example.netflix_android.ViewModel.MoviesViewModel;
import com.example.netflix_android.ViewModel.MoviesViewModelFactory;
import java.util.List;
import java.util.Map;

public class AdminActivity extends AppCompatActivity {
    private static final String TAG = "AdminActivity";

    private RecyclerView itemsRecyclerView;
    private MoviesAdapter movieAdapter;
    private AdminCategoryAdapter adminCategoryAdapter;
    private CategoryAdapter categoryAdapter;

    private MoviesViewModel moviesViewModel;
    private CategoryViewModel categoryViewModel;
    private CategoryRepository categoryRepository;
    private LiveData<List<Category>> categoryLiveData;
    private Button addMovieButton, addCategoryButton;
    private MaterialButton toggleMovies, toggleCategories;
    private MaterialButtonToggleGroup toggleGroup;
    private boolean isViewingMovies = true; // ✅ Track current tab

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin_settings);
        Log.d(TAG, "⚙️ Admin Panel Opened");

        // ✅ Initialize UI Components
        itemsRecyclerView = findViewById(R.id.admin_recycler_view);
        addMovieButton = findViewById(R.id.button_add_movie);
        addCategoryButton = findViewById(R.id.button_add_category);
        toggleGroup = findViewById(R.id.toggle_group);
        toggleMovies = findViewById(R.id.toggle_movies);
        toggleCategories = findViewById(R.id.toggle_categories);

        // ✅ Initialize ViewModel for movies
        moviesViewModel = new ViewModelProvider(this, new MoviesViewModelFactory(this)).get(MoviesViewModel.class);
        categoryViewModel = new ViewModelProvider(this, new CategoryViewModelFactory(this)).get(CategoryViewModel.class);

        // ✅ Initialize Category Repository
        categoryRepository = new CategoryRepository(this);

        // ✅ Default view: Movies
        loadMovies();

        // ✅ Handle Add Movie Button
        addMovieButton.setOnClickListener(v -> {
            Intent intent = new Intent(AdminActivity.this, MovieFormActivity.class);
            startActivity(intent);
        });

        // ✅ Handle Add Category Button
        addCategoryButton.setOnClickListener(v -> {
            Log.d(TAG, "📂 Add Category Clicked");
            Intent intent = new Intent(AdminActivity.this, AddCategoryActivity.class);
            startActivity(intent);
        });

        // ✅ Handle Toggle Selection
        toggleGroup.addOnButtonCheckedListener((group, checkedId, isChecked) -> {
            if (isChecked) {
                if (checkedId == R.id.toggle_movies) {
                    Log.d(TAG, "🎬 Viewing Movies");
                    isViewingMovies = true;
                    loadMovies();
                } else if (checkedId == R.id.toggle_categories) {
                    Log.d(TAG, "📂 Viewing Categories");
                    isViewingMovies = false;
                    loadCategories();
                }
            }
        });
    }

    // ✅ Load Movies in Admin Panel
    private void loadMovies() {
        moviesViewModel.getMovies().observe(this, moviesResultsList -> {
            if (moviesResultsList != null && !moviesResultsList.isEmpty()) {
                Map<String, List<Movie>> categorizedMovies = moviesViewModel.getMoviesGroupedByCategory(moviesResultsList);

                // ✅ Set up RecyclerView with Categories
                itemsRecyclerView.setLayoutManager(new LinearLayoutManager(this));
                categoryAdapter = new CategoryAdapter(this, categorizedMovies);
                itemsRecyclerView.setAdapter(categoryAdapter);

                Log.d(TAG, "✅ Movies loaded and categorized: " + moviesResultsList.size());
            } else {
                Log.e(TAG, "⚠️ No movies found.");
            }
        });
    }

    // ✅ Load Categories in Admin Panel
    public void loadCategories() {
        itemsRecyclerView.setLayoutManager(new GridLayoutManager(this, 2));

        categoryLiveData = categoryRepository.getCategories();
        categoryLiveData.observe(this, categories -> {
            if (categories != null && !categories.isEmpty()) {
                adminCategoryAdapter = new AdminCategoryAdapter(this, categories, categoryViewModel);
                itemsRecyclerView.setAdapter(adminCategoryAdapter);
                Log.d(TAG, "✅ Categories loaded: " + categories.size());
            } else {
                Log.e(TAG, "⚠️ No categories found.");
            }
        });
    }

    // ✅ Refresh content when returning to Admin Panel
    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "🔄 AdminActivity Resumed - Refreshing content...");

        if (isViewingMovies) {
            loadMovies();
        } else {
            loadCategories();
        }
    }
}
