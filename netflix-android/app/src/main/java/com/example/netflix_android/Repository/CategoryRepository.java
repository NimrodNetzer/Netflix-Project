package com.example.netflix_android.Repository;

import android.content.Context;
import android.util.Log;
import androidx.lifecycle.LiveData;
import com.example.netflix_android.Api.CategoryApi;
import com.example.netflix_android.Database.AppDatabase;
import com.example.netflix_android.Database.CategoryDao;
import com.example.netflix_android.Entities.Category;
import com.example.netflix_android.Network.RetrofitClient;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

public class CategoryRepository {
    private static final String TAG = "CategoryRepository";
    private final CategoryDao categoryDao;
    private final CategoryApi categoryApi;
    private final ExecutorService executorService = Executors.newFixedThreadPool(2);

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
                    Log.d(TAG, "✅ Categories fetched successfully");
                } else {
                    logErrorResponse("fetch categories", response);
                }
            }

            @Override
            public void onFailure(Call<List<Category>> call, Throwable t) {
                Log.e(TAG, "❌ Network error while fetching categories", t);
            }
        });
    }

    public void addCategory(Category category) {
        // ✅ Step 1: Insert locally first so UI updates immediately
        executorService.execute(() -> categoryDao.insertAll(Collections.singletonList(category)));

        // ✅ Step 2: Sync with server in background
        categoryApi.createCategory(category).enqueue(new Callback<Category>() {
            @Override
            public void onResponse(Call<Category> call, Response<Category> response) {
                if (response.isSuccessful() && response.body() != null) {
                    // ✅ Step 3: Replace local entry with server's version (in case ID or fields change)
                    executorService.execute(() -> categoryDao.insertAll(Collections.singletonList(response.body())));
                    Log.d(TAG, "✅ Category synced with server: " + response.body().getName());
                } else {
                    logErrorResponse("add category", response);
                }
            }

            @Override
            public void onFailure(Call<Category> call, Throwable t) {
                Log.e(TAG, "Network error while adding category", t);
            }
        });
    }


    public void updateCategory(Category category) {
        categoryApi.updateCategory(category.getId(), category).enqueue(new Callback<Category>() {
            @Override
            public void onResponse(Call<Category> call, Response<Category> response) {
                if (response.isSuccessful() && response.body() != null) {
                    executorService.execute(() -> categoryDao.insertAll(Collections.singletonList(response.body())));
                    Log.d(TAG, "✅ Category updated successfully: " + response.body().getName());
                } else {
                    logErrorResponse("update category", response);
                }
            }

            @Override
            public void onFailure(Call<Category> call, Throwable t) {
                Log.e(TAG, "❌ Network error while updating category", t);
            }
        });
    }

    public void deleteCategory(String categoryId) {
        categoryApi.deleteCategory(categoryId).enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                if (response.isSuccessful()) {
                    //executorService.execute(() -> categoryDao.deleteCategory(categoryId));
                    Log.d(TAG, "✅ Category deleted successfully (ID: " + categoryId + ")");
                } else {
                    logErrorResponse("delete category", response);
                }
            }

            @Override
            public void onFailure(Call<Void> call, Throwable t) {
                Log.e(TAG, "❌ Network error while deleting category", t);
            }
        });
    }

    private void logErrorResponse(String action, Response<?> response) {
        Log.e(TAG, "❌ Failed to " + action + ". HTTP Code: " + response.code());
        try {
            Log.e(TAG, "Response error: " + response.errorBody().string());
        } catch (Exception e) {
            Log.e(TAG, "Error reading response body", e);
        }
    }
}
