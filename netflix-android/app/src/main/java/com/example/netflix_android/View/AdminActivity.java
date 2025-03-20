package com.example.netflix_android.View;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.example.netflix_android.Adapters.AdminCategoryAdapter;
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
    private AdminCategoryAdapter AdminCategoryAdapter;

    private  CategoryAdapter CategoryAdapter;

    private MoviesViewModel moviesViewModel;
    private CategoryRepository categoryRepository;
    private LiveData<List<Category>> categoryLiveData;
    private Button addMovieButton, addCategoryButton;
    private MaterialButton toggleMovies, toggleCategories;
    private MaterialButtonToggleGroup toggleGroup;

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

        // ✅ Initialize Category Repository
        categoryRepository = new CategoryRepository(this);

        // ✅ Default view: Movies
        loadMovies();

        // ✅ Handle Add Movie Button
        addMovieButton.setOnClickListener(v -> {
            Log.d(TAG, "🎬 Add Movie Clicked");
            // TODO: Implement add movie functionality
        });

        // ✅ Handle Add Category Button
        addCategoryButton.setOnClickListener(v -> {
            Log.d(TAG, "📂 Add Category Clicked");
            // TODO: Implement add category functionality
        });

        // ✅ Handle Toggle Selection
        toggleGroup.addOnButtonCheckedListener((group, checkedId, isChecked) -> {
            if (isChecked) {
                if (checkedId == R.id.toggle_movies) {
                    Log.d(TAG, "🎬 Viewing Movies");
                    loadMovies();
                } else if (checkedId == R.id.toggle_categories) {
                    Log.d(TAG, "📂 Viewing Categories");
                    loadCategories();
                }
            }
        });
    }

    // ✅ Load Movies in Admin Panel (Similar to MainActivity)
    private void loadMovies() {
        moviesViewModel.getMovies().observe(this, moviesResultsList -> {
            if (moviesResultsList != null && !moviesResultsList.isEmpty()) {
                // ✅ Categorize Movies
                Map<String, List<Movie>> categorizedMovies = moviesViewModel.getMoviesGroupedByCategory(moviesResultsList);

                // ✅ Set up RecyclerView with Categories
                itemsRecyclerView.setLayoutManager(new LinearLayoutManager(this));
                CategoryAdapter = new CategoryAdapter(this, categorizedMovies);
                itemsRecyclerView.setAdapter(CategoryAdapter);

                Log.d(TAG, "✅ Movies loaded and categorized: " + moviesResultsList.size());
            } else {
                Log.e(TAG, "⚠️ No movies found.");
            }
        });
    }


    // ✅ Load Categories (Using CategoryRepository)
    private void loadCategories() {
        itemsRecyclerView.setLayoutManager(new GridLayoutManager(this, 2));
        categoryLiveData = categoryRepository.getCategories();
        categoryLiveData.observe(this, categories -> {
            if (categories != null && !categories.isEmpty()) {
                AdminCategoryAdapter = new AdminCategoryAdapter(this, categories);
                itemsRecyclerView.setAdapter(AdminCategoryAdapter);
                Log.d(TAG, "✅ Categories loaded: " + categories.size());
            } else {
                Log.e(TAG, "⚠️ No categories found.");
            }
        });
    }
}
