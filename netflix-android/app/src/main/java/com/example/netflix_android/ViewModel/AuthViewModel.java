package com.example.netflix_android.ViewModel;


import android.content.Context;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.ViewModel;
import com.example.netflix_android.Entities.User;
import com.example.netflix_android.Repository.UserRepository;

public class AuthViewModel extends ViewModel {
    private final UserRepository userRepository;

    public AuthViewModel(Context context) {
        userRepository = new UserRepository(context); // Context will be passed from Activity
    }

    public LiveData<Boolean> login(String email, String password) {
        return userRepository.login(email, password);
    }

    public LiveData<Boolean> signup(User user) {
        return userRepository.signup(user);
    }
}