package com.example.netflix_android.View;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import com.example.netflix_android.R;
import com.example.netflix_android.ViewModel.AuthViewModel;
import com.example.netflix_android.ViewModel.AuthViewModelFactory;

public class LoginActivity extends AppCompatActivity {
    private AuthViewModel authViewModel;
    private EditText emailEditText, passwordEditText;
    private Button loginButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        // Initialize ViewModel with Factory
        authViewModel = new ViewModelProvider(this, new AuthViewModelFactory(this))
                .get(AuthViewModel.class);

        // Find Views
        emailEditText = findViewById(R.id.email);
        passwordEditText = findViewById(R.id.password);
        loginButton = findViewById(R.id.login_button);

        // Login Button Click
        loginButton.setOnClickListener(view -> login());
    }

    private void login() {
        String email = emailEditText.getText().toString().trim();
        String password = passwordEditText.getText().toString().trim();

        if (email.isEmpty() || password.isEmpty()) {
            Toast.makeText(this, "Please enter email and password", Toast.LENGTH_SHORT).show();
            return;
        }

        // Call API through ViewModel
        authViewModel.login(email, password).observe(this, success -> {
            if (success) {
                Toast.makeText(this, "Login Successful!", Toast.LENGTH_SHORT).show();
                startActivity(new Intent(LoginActivity.this, MainActivity.class));
                finish(); // Prevent back navigation
            } else {
                Toast.makeText(this, "Login Failed. Check your credentials!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}
