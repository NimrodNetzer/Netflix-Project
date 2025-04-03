package com.example.netflix_android.View;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.VideoView;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.example.netflix_android.Adapters.CategoryAdapter;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.Entities.SearchResult;
import com.example.netflix_android.R;
import com.example.netflix_android.Utils.Constants;
import com.example.netflix_android.Utils.SessionManager;
import com.example.netflix_android.ViewModel.MoviesViewModel;
import com.example.netflix_android.ViewModel.MoviesViewModelFactory;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private RecyclerView categoriesRecyclerView;
    private CategoryAdapter categoryAdapter;
    private MoviesViewModel moviesViewModel;
    private VideoView featuredVideo;
    private TextView featuredVideoDescription;

    // Top menu items...
    private ImageView searchIcon, netflixLogo;
    private Button exitButton, adminButton;
    private Movie featuredMovie;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG, "🚀 App Started - Fetching Movies...");

        // Set up top menu
        setupTopMenu();

        // Initialize UI components
        featuredVideo = findViewById(R.id.featured_video);
        featuredVideoDescription = findViewById(R.id.featured_video_description);
        categoriesRecyclerView = findViewById(R.id.categories_recycler_view);
        categoriesRecyclerView.setLayoutManager(new LinearLayoutManager(this));

        // Initialize ViewModel
        moviesViewModel = new ViewModelProvider(this, new MoviesViewModelFactory(this)).get(MoviesViewModel.class);

        // Load movies for the first time
        loadMovies();
    }

    // ✅ Fetch movies and update UI
    private void loadMovies() {
        moviesViewModel.getMovies().observe(this, moviesResultsList -> {
            if (moviesResultsList != null && !moviesResultsList.isEmpty()) {
                Map<String, List<Movie>> categorizedMovies = moviesViewModel.getMoviesGroupedByCategory(moviesResultsList);

                // ✅ Set up the featured video using the first available movie
                for (List<Movie> movieList : categorizedMovies.values()) {
                    if (!movieList.isEmpty()) {
                        featuredMovie = movieList.get(0);
                        break;
                    }
                }

                if (featuredMovie != null) {
                    String videoUrl = featuredMovie.getVideo();

                    // ✅ Debugging: Ensure `videoUrl` is retrieved
                    if (videoUrl == null || videoUrl.isEmpty()) {
                        Log.e(TAG, "❌ No video URL found for movie: " + featuredMovie.getName());
                    } else {
                        Log.d(TAG, "🎬 Video URL retrieved: " + videoUrl);
                    }

                    // ✅ Set sample video for autoplay
                    featuredVideo.setVideoURI(Uri.parse(Constants.BASE_URL + videoUrl.replace("\\", "/")));

                    // Start auto-play
                    featuredVideo.setOnPreparedListener(mp -> {
                        mp.setLooping(true);
                        featuredVideo.start();
                    });
                    final String title;
                    final String imageUrl;
                    final String movieId;
                    final String details;
                    final String description;
                    final String video;
                    final String quality;
                    final String category;
                    final String duration;
                    final String age;
                    final String year;
                    Movie item = featuredMovie;
                    Movie movie = (Movie) item;
                    title = movie.getName();
                    imageUrl = Constants.BASE_URL + movie.getPicture().replace("\\", "/");
                    movieId = movie.getId();
                    description = movie.getDescription();
                    video = Constants.BASE_URL + movie.getVideo().replace("\\", "/");
                    quality = movie.getQuality();
                    duration = movie.getTime();
                    age = movie.getAge() + "+";
                    year = movie.getReleaseDate() != null
                            ? String.valueOf(movie.getReleaseDate().getYear() + 1900)
                            : "N/A";
                    category = (movie.getCategories() != null && !movie.getCategories().isEmpty())
                            ? movie.getCategories().get(0).getName()
                            : "N/A";
                    details = year + " | " + age + " | " + duration;

                    // ✅ Pass movie data to `MovieDetailActivity`
                    featuredVideo.setOnClickListener(v -> {
                        Intent intent = new Intent(MainActivity.this, MovieDetailActivity.class);
                        intent.putExtra("movie_id", featuredMovie.getId());
                        intent.putExtra("movie_title", featuredMovie.getName());
                        intent.putExtra("movie_image", Constants.BASE_URL + featuredMovie.getPicture().replace("\\", "/"));
                        intent.putExtra("movie_details", "2025  |  " + featuredMovie.getAge() + "+  |  " + featuredMovie.getTime());
                        intent.putExtra("movie_description", featuredMovie.getDescription());
                        intent.putExtra("video_url", Constants.BASE_URL + videoUrl.replace("\\", "/"));
                        intent.putExtra("movie_year", year);
                        intent.putExtra("movie_duration", duration);
                        intent.putExtra("movie_age", age);
                        intent.putExtra("movie_quality", quality);
                        intent.putExtra("chosen_category", category);
                        startActivity(intent);
                    });

                    featuredVideoDescription.setText(featuredMovie.getDescription());
                } else {
                    Log.e(TAG, "⚠️ No featured movie found!");
                }

                // ✅ Set up RecyclerView with categorized movies
                categoryAdapter = new CategoryAdapter(this, categorizedMovies);
                categoriesRecyclerView.setAdapter(categoryAdapter);
            } else {
                Log.e(TAG, "⚠️ No movies found.");
            }
        });
    }

    private void setupTopMenu() {
        try {
            searchIcon = findViewById(R.id.icon_search);
            netflixLogo = findViewById(R.id.netflix_logo);
            exitButton = findViewById(R.id.button_exit);
            adminButton = findViewById(R.id.button_admin);

            if (searchIcon == null || netflixLogo == null || exitButton == null || adminButton == null) {
                Log.e(TAG, "❌ One or more top menu items are missing in activity_main.xml");
                return;
            }

            // ✅ Show admin button if user is an admin
            SessionManager sessionManager = new SessionManager(this);
            boolean isAdmin = sessionManager.isAdmin();

            if (isAdmin) {
                adminButton.setVisibility(View.VISIBLE);
                adminButton.setOnClickListener(v -> {
                    Log.d(TAG, "👑 Admin Panel clicked");
                    startActivity(new Intent(MainActivity.this, AdminActivity.class));
                });
            } else {
                adminButton.setVisibility(View.GONE);
            }

            // ✅ Handle Netflix Logo Click - Refresh page
            netflixLogo.setOnClickListener(v -> {
                Log.d(TAG, "🔄 Netflix logo clicked - Refreshing main screen");
                recreate();
            });

            // ✅ Handle Search Icon Click
            searchIcon.setOnClickListener(v -> {
                Log.d(TAG, "🔍 Search icon clicked");
                startActivity(new Intent(MainActivity.this, SearchActivity.class));
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

    // ✅ Refresh movie list when returning to `MainActivity`
    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "🔄 onResume called - Refreshing movies list.");
        loadMovies(); // Reload movies every time the activity is resumed
    }
}
