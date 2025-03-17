package com.example.netflix_android.View;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.bumptech.glide.Glide;
import com.example.netflix_android.Adapters.MoviesAdapter;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.R;
import com.example.netflix_android.ViewModel.RecommendationViewModel;
import com.example.netflix_android.ViewModel.RecommendationViewModelFactory;

import java.util.ArrayList;
import java.util.List;

public class MovieDetailActivity extends AppCompatActivity {
    private ImageView movieThumbnail, backButton;
    private TextView movieTitle, movieDetails, movieDescription;
    private Button playButton;
    private RecyclerView recommendationsRecyclerView;
    private MoviesAdapter recommendationsAdapter;
    private RecommendationViewModel recommendationViewModel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_movie_detail);

        // Bind UI elements
        movieThumbnail = findViewById(R.id.movie_thumbnail);
        movieTitle = findViewById(R.id.movie_title);
        movieDetails = findViewById(R.id.movie_details);
        movieDescription = findViewById(R.id.movie_description);
        playButton = findViewById(R.id.play_button);
        backButton = findViewById(R.id.back_button);
        recommendationsRecyclerView = findViewById(R.id.recommendations_list);

        // Get data from Intent
        Intent intent = getIntent();
        String imageUrl = intent.getStringExtra("movie_image");
        String title = intent.getStringExtra("movie_title");
        String details = intent.getStringExtra("movie_details");
        String description = intent.getStringExtra("movie_description");
        String movieId = intent.getStringExtra("movie_id"); // Needed for recommendations

        // Debugging: Check if movieId is null
        if (movieId == null || movieId.trim().isEmpty()) {
            movieId = "default_movie_id"; // Assign a default ID or prevent API call
            android.util.Log.e("MovieDetailActivity", "Received null movieId from Intent!");
        } else {
            android.util.Log.d("MovieDetailActivity", "Fetched movieId: " + movieId);
        }

        // Set movie details
        movieTitle.setText(title);
        movieDetails.setText(details);
        movieDescription.setText(description);

        // Load movie poster
        Glide.with(this)
                .load(imageUrl)
                .placeholder(android.R.drawable.ic_menu_gallery)
                .error(android.R.drawable.stat_notify_error)
                .into(movieThumbnail);

        // Play button action (TODO: Add logic)
        playButton.setOnClickListener(v -> {
            // TODO: Play the movie
        });

        // Back button to close the detail screen
        backButton.setOnClickListener(v -> finish());

        // Initialize ViewModel with Factory
        RecommendationViewModelFactory factory = new RecommendationViewModelFactory(this);
        recommendationViewModel = new ViewModelProvider(this, factory).get(RecommendationViewModel.class);

        // Fetch and display recommendations only if movieId is valid
        if (!movieId.equals("default_movie_id")) {
            recommendationViewModel.getRecommendedMovies(movieId).observe(this, this::displayRecommendations);
        }
    }


    private void displayRecommendations(List<Movie> movies) {
        if (movies == null || movies.isEmpty()) {
            android.util.Log.d("RecommendationDebug", "No recommendations found.");
            movies = new ArrayList<>(); // Avoid null reference
        }
        recommendationsAdapter = new MoviesAdapter(this, movies);
        recommendationsRecyclerView.setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false));
        recommendationsRecyclerView.setAdapter(recommendationsAdapter);
    }

}