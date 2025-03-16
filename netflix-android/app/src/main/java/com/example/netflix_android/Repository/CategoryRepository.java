package com.example.netflix_android.Repository;

import android.content.Context;
import android.util.Log;
import androidx.lifecycle.LiveData;
import com.example.netflix_android.Api.CategoryApi;
import com.example.netflix_android.Database.AppDatabase;
import com.example.netflix_android.Database.CategoryDao;
import com.example.netflix_android.Entities.Category;
import com.example.netflix_android.Network.RetrofitClient;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class CategoryRepository {
    private CategoryDao categoryDao;
    private CategoryApi categoryApi;
    private ExecutorService executorService = Executors.newFixedThreadPool(2);

    public CategoryRepository(Context context) {
        AppDatabase db = AppDatabase.getInstance(context);
        categoryDao = db.categoryDao();
        categoryApi = RetrofitClient.getRetrofitInstance(context).create(CategoryApi.class);
    }

    public LiveData<List<Category>> getCategories() {
        fetchCategoriesFromApi();
        return categoryDao.getAllCategories();
    }

    private void fetchCategoriesFromApi() {
        categoryApi.getCategories().enqueue(new Callback<List<Category>>() {
            @Override
            public void onResponse(Call<List<Category>> call, Response<List<Category>> response) {
                if (response.isSuccessful() && response.body() != null) {
                    executorService.execute(() -> {
                        categoryDao.deleteAll();
                        categoryDao.insertAll(response.body());
                    });
                }
            }

            @Override
            public void onFailure(Call<List<Category>> call, Throwable t) {
                Log.e("CategoryRepository", "Failed to fetch categories", t);
            }
        });
    }
}
