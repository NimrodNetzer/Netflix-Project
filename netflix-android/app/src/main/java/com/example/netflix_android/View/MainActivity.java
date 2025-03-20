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
import com.example.netflix_android.Utils.Constants;
import com.example.netflix_android.ViewModel.MoviesViewModel;
import com.example.netflix_android.ViewModel.MoviesViewModelFactory;
import java.util.List;
import java.util.Map;
import android.net.Uri;
import android.widget.TextView;
import android.widget.VideoView;
public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private RecyclerView categoriesRecyclerView;
    private CategoryAdapter categoryAdapter;
    private MoviesViewModel moviesViewModel;
    private VideoView featuredVideo; // Featured Video View
    private TextView featuredVideoDescription; // Description TextView

    // Top menu items...
    private ImageView searchIcon, settingsIcon, netflixLogo;
    private Button exitButton;
    private Movie featuredMovie;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main); // Ensure this layout now contains the featured video

        Log.d(TAG, "🚀 App Started - Fetching Movies...");

        // Set up top menu
        setupTopMenu();

        // Initialize featured video view
        featuredVideo = findViewById(R.id.featured_video);
        featuredVideoDescription = findViewById(R.id.featured_video_description);
        // Set up RecyclerView for categories
        categoriesRecyclerView = findViewById(R.id.categories_recycler_view);
        categoriesRecyclerView.setLayoutManager(new LinearLayoutManager(this));

        // Initialize ViewModel for movies
        moviesViewModel = new ViewModelProvider(this, new MoviesViewModelFactory(this)).get(MoviesViewModel.class);

        // Fetch movies and display them
        moviesViewModel.getMovies().observe(this, moviesResultsList -> {
            if (moviesResultsList != null && !moviesResultsList.isEmpty()) {
                Map<String, List<Movie>> categorizedMovies = moviesViewModel.getMoviesGroupedByCategory(moviesResultsList);

                // Set up the featured video using the first movie from the first available category
                for (List<Movie> movieList : categorizedMovies.values()) {
                    if (!movieList.isEmpty()) {
                        featuredMovie = movieList.get(0);
                        break;
                    }
                }
                if (featuredMovie != null) {
                    // Assume getVideoUrl() returns the URL for the video
                    String videoUrl = featuredMovie.getVideo();
                    featuredVideo.setVideoURI(Uri.parse("https://www.learningcontainer.com/wp-content/uploads/2020/05/sample-mp4-file.mp4"));

                    // Start auto-play once the video is ready
                    featuredVideo.setOnPreparedListener(mp -> {
                        mp.setLooping(true); // Optional: loop the video
                        featuredVideo.start();
                    });

                    // When clicked, open the MovieDetailActivity like a movie box
                    featuredVideo.setOnClickListener(v -> {
                        Intent intent = new Intent(MainActivity.this, MovieDetailActivity.class);
                        intent.putExtra("movie_id", featuredMovie.getId());
                        intent.putExtra("movie_title", featuredMovie.getName());
                        intent.putExtra("movie_image", Constants.BASE_URL + featuredMovie.getPicture().replace("\\", "/"));
                        intent.putExtra("movie_details", "2025  |  " + featuredMovie.getAge() + "+  |  " + featuredMovie.getTime());
                        intent.putExtra("movie_description", featuredMovie.getDescription());
                        startActivity(intent);
                    });
                    featuredVideoDescription.setText(featuredMovie.getDescription());
                }

                // Set up categories adapter for the RecyclerView
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
            settingsIcon.setOnClickListener(v -> {
                Log.d(TAG, "⚙️ Settings icon clicked - Opening Update Mode with Temporary Data");

                Intent intent = new Intent(MainActivity.this, AddCategoryActivity.class);
                intent.putExtra("category_id", "67dbc9e301f8a1a99068232d"); // ✅ Temporary ID
                intent.putExtra("category_name", "Temporary Category"); // ✅ Temporary Name
                intent.putExtra("category_promoted", true); // ✅ Temporary Promoted Status
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
