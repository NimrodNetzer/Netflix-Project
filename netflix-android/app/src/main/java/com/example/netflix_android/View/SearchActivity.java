package com.example.netflix_android.View;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ProgressBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.example.netflix_android.Adapters.MoviesAdapter;
import com.example.netflix_android.Entities.SearchResult;
import com.example.netflix_android.R;
import com.example.netflix_android.ViewModel.SearchViewModel;
import com.example.netflix_android.ViewModel.SearchViewModelFactory;
import com.example.netflix_android.R;
import java.util.List;

public class SearchActivity extends AppCompatActivity {
    private static final String TAG = "SearchActivity";
    private SearchViewModel searchViewModel;
    private RecyclerView searchResultsRecyclerView;
    private MoviesAdapter searchResultsAdapter;
    private EditText searchInput;
    private ImageView searchButton, backButton;
    private ProgressBar loadingIndicator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);
        Log.d(TAG, "🔍 SearchActivity Started");

        // ✅ Initialize UI components
        searchResultsRecyclerView = findViewById(R.id.search_results_list);
        searchInput = findViewById(R.id.search_input);
        searchButton = findViewById(R.id.search_button);
        backButton = findViewById(R.id.back_button);
        loadingIndicator = findViewById(R.id.loading_indicator);

        searchResultsRecyclerView.setLayoutManager(new LinearLayoutManager(this));

        // ✅ Initialize ViewModel using Factory
        SearchViewModelFactory factory = new SearchViewModelFactory(this);
        searchViewModel = new ViewModelProvider(this, factory).get(SearchViewModel.class);

        // ✅ Handle search button click
        searchButton.setOnClickListener(v -> {
            String query = searchInput.getText().toString().trim();
            if (!query.isEmpty()) {
                searchMovies(query);
            }
        });

        // ✅ Handle back button click
        backButton.setOnClickListener(v -> finish());
    }

    // ✅ Fetch search results
    private void searchMovies(String query) {
        Log.d(TAG, "🔍 Searching for: " + query);
        loadingIndicator.setVisibility(View.VISIBLE); // Show loading
        searchViewModel.searchMovies(query).observe(this, this::displaySearchResults);
    }

    // ✅ Display search results in RecyclerView
    private void displaySearchResults(List<SearchResult> results) {
        loadingIndicator.setVisibility(View.GONE); // Hide loading
        if (results != null && !results.isEmpty()) {
            searchResultsAdapter = new MoviesAdapter(this, results);
            searchResultsRecyclerView.setAdapter(searchResultsAdapter);
            Log.d(TAG, "✅ Search results loaded: " + results.size() + " movies found.");
        } else {
            Log.d(TAG, "⚠️ No results found.");
        }
    }
}
