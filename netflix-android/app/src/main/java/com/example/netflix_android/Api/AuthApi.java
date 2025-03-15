package com.example.netflix_android.Api;

import com.example.netflix_android.Entities.User;
import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.POST;

public interface AuthApi {
    @POST("/api/tokens")
    Call<User> login(@Body User user);

    @POST("/api/users")
    Call<Void> signup(@Body User user);
}
