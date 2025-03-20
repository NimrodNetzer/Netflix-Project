package com.example.netflix_android.View;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import com.example.netflix_android.Repository.MovieRepository;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.bumptech.glide.Glide;
import com.example.netflix_android.Adapters.MoviesAdapter;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.R;
import com.example.netflix_android.Utils.SessionManager;
import com.example.netflix_android.ViewModel.MovieViewModel;
import com.example.netflix_android.ViewModel.MovieViewModelFactory;
import com.example.netflix_android.ViewModel.RecommendationViewModel;
import com.example.netflix_android.ViewModel.RecommendationViewModelFactory;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import java.util.ArrayList;
import java.util.List;

public class MovieDetailActivity extends AppCompatActivity {
    private static final String TAG = "MovieDetailActivity";

    private ImageView movieThumbnail;
    private TextView movieTitle, movieDetails, movieDescription;
    private Button playButton;
    private RecyclerView recommendationsRecyclerView;
    private MoviesAdapter recommendationsAdapter;
    private RecommendationViewModel recommendationViewModel;
    private MovieViewModel movieViewModel;
    private FloatingActionButton editButton, deleteButton;
    private String videoUrl;
    private String movieId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_movie_detail);

        // ✅ Bind UI elements
        movieThumbnail = findViewById(R.id.movie_thumbnail);
        movieTitle = findViewById(R.id.movie_title);
        movieDetails = findViewById(R.id.movie_details);
        movieDescription = findViewById(R.id.movie_description);
        playButton = findViewById(R.id.play_button);
        recommendationsRecyclerView = findViewById(R.id.recommendations_list);
        editButton = findViewById(R.id.edit_button);
        deleteButton = findViewById(R.id.delete_button);

        // ✅ Get data from Intent
        Intent intent = getIntent();
        String imageUrl = intent.getStringExtra("movie_image");
        String title = intent.getStringExtra("movie_title");
        String details = intent.getStringExtra("movie_details");
        String description = intent.getStringExtra("movie_description");
        movieId = intent.getStringExtra("movie_id");
        videoUrl = intent.getStringExtra("video_url");

        // ✅ Debugging: Log received video URL
        if (videoUrl == null || videoUrl.trim().isEmpty()) {
            Log.e(TAG, "❌ No video URL received! Using default sample video.");
            videoUrl = "https://www.learningcontainer.com/wp-content/uploads/2020/05/sample-mp4-file.mp4";
        } else {
            Log.d(TAG, "🎬 Video URL received: " + videoUrl);
        }

        // ✅ Set movie details
        movieTitle.setText(title);
        movieDetails.setText(details);
        movieDescription.setText(description);

        // ✅ Load movie poster
        Glide.with(this)
                .load(imageUrl)
                .placeholder(android.R.drawable.ic_menu_gallery)
                .error(android.R.drawable.stat_notify_error)
                .into(movieThumbnail);
        // ✅ Initialize ViewModel with Factory
        RecommendationViewModelFactory recFactory = new RecommendationViewModelFactory(this);
        recommendationViewModel = new ViewModelProvider(this, recFactory).get(RecommendationViewModel.class);

        // ✅ Play button action - Start VideoPlayerActivity
        playButton.setOnClickListener(v -> {
            Intent videoIntent = new Intent(MovieDetailActivity.this, VideoPlayerActivity.class);
            videoIntent.putExtra("video_url", videoUrl);
            startActivity(videoIntent);
            recommendationViewModel.addRecommendation(movieId);
        });



        MovieViewModelFactory movieFactory = new MovieViewModelFactory(this);
        movieViewModel = new ViewModelProvider(this, movieFactory).get(MovieViewModel.class);

        // ✅ Fetch and display recommendations only if movieId is valid
        if (movieId != null && !movieId.trim().isEmpty()) {
            recommendationViewModel.getRecommendedMovies(movieId).observe(this, this::displayRecommendations);
        } else {
            Log.e(TAG, "❌ Invalid movie ID received!");
        }

        // ✅ Check if user is admin and show buttons
        SessionManager sessionManager = new SessionManager(this);
        if (sessionManager.isAdmin()) {
            editButton.setVisibility(View.VISIBLE);
            deleteButton.setVisibility(View.VISIBLE);
            setupAdminControls();
        } else {
            editButton.setVisibility(View.GONE);
            deleteButton.setVisibility(View.GONE);
        }
    }

    private void displayRecommendations(List<Movie> movies) {
        if (movies == null || movies.isEmpty()) {
            Log.d(TAG, "No recommendations found.");
            movies = new ArrayList<>();
        }
        recommendationsAdapter = new MoviesAdapter(this, movies);
        recommendationsRecyclerView.setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false));
        recommendationsRecyclerView.setAdapter(recommendationsAdapter);
    }

    // ✅ Setup Admin Controls
    private void setupAdminControls() {
        // Delete Movie Button
        // Delete Movie Button
        deleteButton.setOnClickListener(v -> {
            if (movieId == null || movieId.trim().isEmpty()) {
                Toast.makeText(this, "Movie ID is invalid.", Toast.LENGTH_SHORT).show();
                return;
            }

            Log.d(TAG, "🗑️ Attempting to delete movie: " + movieId);

            movieViewModel.deleteMovie(movieId).observe(this, success -> {
                if (Boolean.TRUE.equals(success)) {
                    Toast.makeText(this, "✅ Movie deleted successfully!", Toast.LENGTH_SHORT).show();
                    // Notify MainActivity/AdminActivity to refresh the list
                    setResult(RESULT_OK);
                    finish(); // Close the activity
                    } else {
                    Toast.makeText(this, "❌ Failed to delete movie.", Toast.LENGTH_SHORT).show();
                }
            });
        });


        // TODO: Add Edit Movie Functionality Here
        editButton.setOnClickListener(v -> {
            Toast.makeText(this, "✏️ Edit functionality coming soon!", Toast.LENGTH_SHORT).show();
        });
    }
}
