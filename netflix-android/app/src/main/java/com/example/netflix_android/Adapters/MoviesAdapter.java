package com.example.netflix_android.Adapters;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.bumptech.glide.Glide;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.R;
import com.example.netflix_android.Utils.Constants;

import java.util.List;

public class MoviesAdapter extends RecyclerView.Adapter<MoviesAdapter.MovieViewHolder> {
    private Context context;
    private List<Movie> movieList;

    public MoviesAdapter(Context context, List<Movie> movieList) {
        this.context = context;
        this.movieList = movieList;
    }

    @NonNull
    @Override
    public MovieViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.movie_card, parent, false);
        return new MovieViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull MovieViewHolder holder, int position) {
        Movie movie = movieList.get(position);

        // Set movie title
        holder.movieTitle.setText(movie.getName());

        // Define your API base URL
        String baseUrl = Constants.BASE_URL;  // Change this to your actual domain

        // Construct the full image URL
        String imageUrl = baseUrl + movie.getPicture().replace("\\", "/"); // Ensure correct URL format

        // Log the final URL to debug if needed
        Log.d("GlideDebug", "Loading image: " + imageUrl);

        // Load movie poster using Glide
        Glide.with(context)
                .load(imageUrl)
                .placeholder(android.R.drawable.ic_menu_gallery) // Default placeholder
                .error(android.R.drawable.stat_notify_error) // Default error icon

                .into(holder.moviePoster);
    }



    @Override
    public int getItemCount() {
        return movieList.size();
    }

    public static class MovieViewHolder extends RecyclerView.ViewHolder {
        ImageView moviePoster;
        TextView movieTitle;

        public MovieViewHolder(@NonNull View itemView) {
            super(itemView);
            moviePoster = itemView.findViewById(R.id.movie_thumbnail);
            movieTitle = itemView.findViewById(R.id.movie_title);
        }
    }
}
