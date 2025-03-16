package com.example.netflix_android.ViewModel;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;
import com.example.netflix_android.Entities.MoviesResults;
import com.example.netflix_android.Repository.MoviesRepository;
import java.util.List;

public class MoviesViewModel extends ViewModel {
    private final MoviesRepository moviesRepository;

    public MoviesViewModel(MoviesRepository moviesRepository) {
        this.moviesRepository = moviesRepository;
    }

    // ✅ Fetch movies from API and store locally
    public LiveData<List<MoviesResults>> getMovies() {
        return moviesRepository.getMovies();
    }

}
