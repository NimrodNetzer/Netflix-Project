package com.example.netflix_android.Repository;

import android.content.Context;
import android.util.Log;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import com.example.netflix_android.Api.AuthApi;
import com.example.netflix_android.Database.AppDatabase;
import com.example.netflix_android.Database.UserDao;
import com.example.netflix_android.Entities.User;
import com.example.netflix_android.Network.RetrofitClient;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class UserRepository {
    private UserDao userDao;
    private AuthApi authApi;
    private ExecutorService executorService = Executors.newFixedThreadPool(2);

    public UserRepository(Context context) {
        AppDatabase db = AppDatabase.getInstance(context);
        userDao = db.userDao();
        authApi = RetrofitClient.getRetrofitInstance().create(AuthApi.class);
    }

    public LiveData<Boolean> signup(User user) {
        MutableLiveData<Boolean> success = new MutableLiveData<>();
        authApi.signup(user).enqueue(new Callback<Void>() {
            @Override
            public void onResponse(Call<Void> call, Response<Void> response) {
                if (response.isSuccessful()) {
                    executorService.execute(() -> userDao.insert(user));
                    success.postValue(true);
                } else {
                    success.postValue(false);
                }
            }

            @Override
            public void onFailure(Call<Void> call, Throwable t) {
                success.postValue(false);
            }
        });
        return success;
    }

    public LiveData<Boolean> login(String email, String password) {
        MutableLiveData<Boolean> success = new MutableLiveData<>();
        User loginUser = new User(email, password, null, null, null);

        Log.d("LoginDebug", "Attempting login with email: " + email);

        authApi.login(loginUser).enqueue(new Callback<User>() {
            @Override
            public void onResponse(Call<User> call, Response<User> response) {
                if (response.isSuccessful() && response.body() != null) {
                    User loggedInUser = response.body();
                    Log.d("LoginDebug", "Login successful: " + loggedInUser.getEmail());

                    executorService.execute(() -> {
                        userDao.deleteAllUsers(); // Clear old user data
                        userDao.insert(loggedInUser); // Save new user
                    });
                    success.postValue(true);
                } else {
                    Log.e("LoginDebug", "Login failed: " + response.code() + " - " + response.message());

                    try {
                        Log.e("LoginDebug", "Error body: " + response.errorBody().string());
                    } catch (Exception e) {
                        Log.e("LoginDebug", "Failed to read error body", e);
                    }

                    success.postValue(false);
                }
            }

            @Override
            public void onFailure(Call<User> call, Throwable t) {
                Log.e("LoginDebug", "Login request failed", t);
                success.postValue(false);
            }
        });
        return success;
    }

    public LiveData<User> getUser(String email) {
        MutableLiveData<User> userLiveData = new MutableLiveData<>();
        executorService.execute(() -> userLiveData.postValue(userDao.getUserByEmail(email)));
        return userLiveData;
    }

    public void logout() {
        executorService.execute(() -> userDao.deleteAllUsers());
    }
}
