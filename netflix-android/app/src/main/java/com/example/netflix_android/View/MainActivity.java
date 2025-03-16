package com.example.netflix_android.View;

import android.os.Bundle;
import android.util.Log;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import com.example.netflix_android.Entities.Category;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.Entities.MoviesResults;
import com.example.netflix_android.Entities.SearchResult;
import com.example.netflix_android.R;
import com.example.netflix_android.Utils.SessionManager;
import com.example.netflix_android.ViewModel.CategoryViewModel;
import com.example.netflix_android.ViewModel.CategoryViewModelFactory;
import com.example.netflix_android.ViewModel.MovieViewModel;
import com.example.netflix_android.ViewModel.MovieViewModelFactory;
import com.example.netflix_android.ViewModel.MoviesViewModel;
import com.example.netflix_android.ViewModel.MoviesViewModelFactory;
import com.example.netflix_android.ViewModel.SearchViewModel;
import com.example.netflix_android.ViewModel.SearchViewModelFactory;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private CategoryViewModel categoryViewModel;
    private MovieViewModel movieViewModel;
    private MoviesViewModel moviesViewModel;
    private SearchViewModel searchViewModel;
    private static final String TAG = "DataDebug";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG, "════════════════════════════════════════════");
        Log.d(TAG, "              MAIN ACTIVITY STARTED         ");
        Log.d(TAG, "════════════════════════════════════════════");

        SessionManager sessionManager = new SessionManager(this);

        // ✅ Check if user is admin
        boolean isAdmin = sessionManager.isAdmin();
        Log.d(TAG, "🔹 Admin Check: " + (isAdmin ? "✅ User is Admin" : "❌ User is Regular"));

        // ✅ Initialize ViewModel Factory for categories
        CategoryViewModelFactory categoryFactory = new CategoryViewModelFactory(this);
        categoryViewModel = new ViewModelProvider(this, categoryFactory).get(CategoryViewModel.class);

        // ✅ Observe categories and log them
        categoryViewModel.getCategories().observe(this, this::logCategories);

        // ✅ Initialize ViewModel Factory for movies
        MovieViewModelFactory movieFactory = new MovieViewModelFactory(this);
        movieViewModel = new ViewModelProvider(this, movieFactory).get(MovieViewModel.class);

        // ✅ Fetch and log movies by ID
        fetchAndLogMovie("7");
        fetchAndLogMovie("32");
        fetchAndLogMovie("58");
        fetchAndLogMovie("15");

        // ✅ Initialize ViewModel Factory for search
        SearchViewModelFactory searchFactory = new SearchViewModelFactory(this);
        searchViewModel = new ViewModelProvider(this, searchFactory).get(SearchViewModel.class);

        // ✅ Perform a search for "99" and log the results
        searchMovies("99");

        // ✅ Initialize ViewModel Factory for movies grouped by categories
        MoviesViewModelFactory moviesFactory = new MoviesViewModelFactory(this);
        moviesViewModel = new ViewModelProvider(this, moviesFactory).get(MoviesViewModel.class);

        // ✅ Fetch and log movies grouped by categories
        fetchMoviesGroupedByCategories();
    }

    private void logCategories(List<Category> categories) {
        Log.d(TAG, "════════════════════════════════════════════");
        Log.d(TAG, "              📂 CATEGORIES LOADED          ");
        Log.d(TAG, "════════════════════════════════════════════");

        if (categories == null || categories.isEmpty()) {
            Log.d(TAG, "⚠️ No categories available.");
        } else {
            for (Category category : categories) {
                Log.d(TAG, "📂 Category: [" + category.getId() + "] " + category.getName());
                Log.d(TAG, "   └ 🔹 Promoted: " + (category.isPromoted() ? "✅ Yes" : "❌ No"));
            }
        }
        Log.d(TAG, "════════════════════════════════════════════");
    }

    private void fetchAndLogMovie(String movieId) {
        Log.d(TAG, "📽️ Fetching movie with ID: " + movieId);
        movieViewModel.getMovieById(movieId).observe(this, movie -> {
            Log.d(TAG, "════════════════════════════════════════════");
            Log.d(TAG, "              🎬 MOVIE DETAILS              ");
            Log.d(TAG, "════════════════════════════════════════════");
            if (movie != null) {
                Log.d(TAG, "🎬 Movie: [" + movie.getId() + "] " + movie.getName());
                Log.d(TAG, "   ├ 🏆 Quality: " + movie.getQuality());
                Log.d(TAG, "   ├ 📅 Release Date: " + movie.getReleaseDate());
                Log.d(TAG, "   └ 🎭 Categories: " + movie.getCategories().size());
            } else {
                Log.d(TAG, "⚠️ Movie not found for ID: " + movieId);
            }
            Log.d(TAG, "════════════════════════════════════════════");
        });
    }

    private void searchMovies(String query) {
        Log.d(TAG, "🔍 Searching for movies with query: " + query);
        searchViewModel.searchMovies(query).observe(this, movies -> {
            Log.d(TAG, "════════════════════════════════════════════");
            Log.d(TAG, "             🔍 SEARCH RESULTS              ");
            Log.d(TAG, "════════════════════════════════════════════");
            if (movies == null || movies.isEmpty()) {
                Log.d(TAG, "⚠️ No movies found for query: " + query);
            } else {
                for (SearchResult movie : movies) {
                    Log.d(TAG, "🔹 Search Result -> 🎬 Movie: [" + movie.getId() + "] " + movie.getName());
                    Log.d(TAG, "   ├ 🏆 Quality: " + movie.getQuality());
                }
            }
            Log.d(TAG, "════════════════════════════════════════════");
        });
    }

    private void fetchMoviesGroupedByCategories() {
        Log.d(TAG, "🎬 Fetching movies grouped by categories...");
        moviesViewModel.getMovies().observe(this, moviesResultsList -> {
            Log.d(TAG, "════════════════════════════════════════════");
            Log.d(TAG, "       🎭 MOVIES GROUPED BY CATEGORIES       ");
            Log.d(TAG, "════════════════════════════════════════════");

            if (moviesResultsList == null || moviesResultsList.isEmpty()) {
                Log.d(TAG, "⚠️ No grouped movies available.");
            } else {
                for (MoviesResults moviesResults : moviesResultsList) {
                    Log.d(TAG, "📂 Category: " + moviesResults.getCategoryName() + " (ID: " + moviesResults.getCategoryId() + ")");
                    Log.d(TAG, "   └ 🔹 Promoted: " + (moviesResults.isPromoted() ? "✅ Yes" : "❌ No"));

                    List<Movie> movies = moviesResults.getMovies();
                    if (movies == null || movies.isEmpty()) {
                        Log.d(TAG, "   └ ⚠️ No movies in this category.");
                    } else {
                        for (Movie movie : movies) {
                            Log.d(TAG, "   ├ 🎬 Movie: [" + movie.getId() + "] " + movie.getName());
                            Log.d(TAG, "   │   ├ 🏆 Quality: " + movie.getQuality());
                            Log.d(TAG, "   │   └ 📅 Release Date: " + movie.getReleaseDate());
                        }
                    }
                    Log.d(TAG, "-------------------------------------------");
                }
            }
            Log.d(TAG, "════════════════════════════════════════════");
        });
    }
}
