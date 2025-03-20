package com.example.netflix_android.View;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.ViewModelProvider;
import com.example.netflix_android.Entities.Category;
import com.example.netflix_android.R;
import com.example.netflix_android.ViewModel.CategoryViewModel;
import com.example.netflix_android.ViewModel.CategoryViewModelFactory;

public class AddCategoryActivity extends AppCompatActivity {
    private EditText categoryNameInput;
    private Button buttonSubmitCategory, buttonCancel, buttonPromoted;
    private boolean isPromoted = false;
    private CategoryViewModel categoryViewModel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_category);

        // Initialize UI components
        categoryNameInput = findViewById(R.id.category_name_input);
        buttonSubmitCategory = findViewById(R.id.button_submit_category);
        buttonCancel = findViewById(R.id.button_cancel);
        buttonPromoted = findViewById(R.id.button_promoted);

        // Initialize ViewModel
        CategoryViewModelFactory factory = new CategoryViewModelFactory(getApplicationContext());
        categoryViewModel = new ViewModelProvider(this, factory).get(CategoryViewModel.class);
        // Handle Promoted/Not Promoted Toggle
        buttonPromoted.setOnClickListener(v -> {
            isPromoted = !isPromoted; // Toggle the boolean value
            buttonPromoted.setText(isPromoted ? "Promoted" : "Not Promoted");
        });

        // Handle Submit Button Click
        buttonSubmitCategory.setOnClickListener(v -> {
            String categoryName = categoryNameInput.getText().toString().trim();
            if (categoryName.isEmpty()) {
                Toast.makeText(this, "Category name cannot be empty", Toast.LENGTH_SHORT).show();
                return;
            }

            // Create new Category object
            Category newCategory = new Category("1", categoryName, isPromoted);

            // Add category via ViewModel
            categoryViewModel.addCategory(newCategory);
            Toast.makeText(this, "Category added successfully", Toast.LENGTH_SHORT).show();
            finish(); // Close the activity
        });

        // Handle Cancel Button Click
        buttonCancel.setOnClickListener(v -> finish());
    }
}
