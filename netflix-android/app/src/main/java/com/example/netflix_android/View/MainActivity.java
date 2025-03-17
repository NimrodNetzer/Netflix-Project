package com.example.netflix_android.View;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageView;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.example.netflix_android.Adapters.CategoryAdapter;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.R;
import com.example.netflix_android.ViewModel.MoviesViewModel;
import com.example.netflix_android.ViewModel.MoviesViewModelFactory;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private RecyclerView categoriesRecyclerView;
    private CategoryAdapter categoryAdapter;
    private MoviesViewModel moviesViewModel;

    // ✅ Top menu items
    private ImageView searchIcon, settingsIcon, netflixLogo;
    private Button exitButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // Ensure activity_main.xml includes the top menu!

        Log.d(TAG, "🚀 App Started - Fetching Movies...");

        // ✅ Set up top menu
        setupTopMenu();

        // ✅ Set up RecyclerView for categories
        categoriesRecyclerView = findViewById(R.id.categories_recycler_view);
        categoriesRecyclerView.setLayoutManager(new LinearLayoutManager(this));

        // ✅ Initialize ViewModel for movies
        moviesViewModel = new ViewModelProvider(this, new MoviesViewModelFactory(this)).get(MoviesViewModel.class);

        // ✅ Fetch movies and display them
        moviesViewModel.getMovies().observe(this, moviesResultsList -> {
            if (moviesResultsList != null && !moviesResultsList.isEmpty()) {
                Map<String, List<Movie>> categorizedMovies = moviesViewModel.getMoviesGroupedByCategory(moviesResultsList);
                categoryAdapter = new CategoryAdapter(this, categorizedMovies);
                categoriesRecyclerView.setAdapter(categoryAdapter);
            } else {
                Log.e(TAG, "⚠️ No movies found.");
            }
        });
    }

    private void setupTopMenu() {
        try {
            // ✅ Get references to UI elements (Ensure these IDs exist in activity_main.xml!)
            searchIcon = findViewById(R.id.icon_search);
            settingsIcon = findViewById(R.id.icon_settings);
            netflixLogo = findViewById(R.id.netflix_logo);
            exitButton = findViewById(R.id.button_exit);

            if (searchIcon == null || settingsIcon == null || netflixLogo == null || exitButton == null) {
                Log.e(TAG, "❌ One or more top menu items are missing in activity_main.xml");
                return; // Prevent NullPointerException
            }

            // ✅ Handle Netflix Logo Click - Refresh page
            netflixLogo.setOnClickListener(v -> {
                Log.d(TAG, "🔄 Netflix logo clicked - Refreshing main screen");
                recreate();
            });

            searchIcon.setOnClickListener(v -> {
                Log.d(TAG, "🔍 Search icon clicked");
                Intent intent = new Intent(MainActivity.this, com.example.netflix_android.View.SearchActivity.class);
                startActivity(intent);
            });



            // ✅ Handle Exit Button - Go Back to WelcomeActivity
            exitButton.setOnClickListener(v -> {
                Log.d(TAG, "🚪 Exit button clicked - Returning to Welcome Screen");
                Intent intent = new Intent(MainActivity.this, WelcomeActivity.class);
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
                startActivity(intent);
                finish();
            });

        } catch (Exception e) {
            Log.e(TAG, "❌ Error setting up top menu", e);
        }
    }
}
