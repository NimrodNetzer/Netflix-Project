package com.example.netflix_android.ViewModel;

import android.content.Context;
import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;
import com.example.netflix_android.Entities.Movie;
import com.example.netflix_android.Repository.MovieRepository;

public class MovieViewModel extends ViewModel {
    private final MovieRepository movieRepository;

    public MovieViewModel(MovieRepository repository) {
        this.movieRepository = repository;
    }

    public LiveData<Movie> getMovieById(String movieId) {
        return movieRepository.getMovieById(movieId);
    }

    public LiveData<Boolean> deleteMovie(String movieId) {
        return movieRepository.deleteMovie(movieId);
    }

}
