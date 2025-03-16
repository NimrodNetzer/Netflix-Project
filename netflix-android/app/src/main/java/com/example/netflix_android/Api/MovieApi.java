package com.example.netflix_android.Api;

import com.example.netflix_android.Entities.Movie;
import java.util.List;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Path;
import retrofit2.http.POST;
import retrofit2.http.Body;
import retrofit2.http.PUT;
import retrofit2.http.DELETE;

public interface MovieApi {


    // Fetch a movie by its ID
    @GET("/api/movies/{id}")
    Call<Movie> getMovieById(@Path("id") String movieId);

    // Create a new movie
    @POST("/api/movies")
    Call<Movie> createMovie(@Body Movie movie);

    // Update an existing movie
    @PUT("/api/movies/{id}")
    Call<Movie> updateMovie(@Path("id") String movieId, @Body Movie movie);

    // Delete a movie
    @DELETE("/api/movies/{id}")
    Call<Void> deleteMovie(@Path("id") String movieId);
}
