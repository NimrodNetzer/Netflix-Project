package com.example.netflix_android.Adapters;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import androidx.annotation.NonNull;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.RecyclerView;
import com.example.netflix_android.Entities.Category;
import com.example.netflix_android.R;
import com.example.netflix_android.View.AddCategoryActivity;
import com.example.netflix_android.View.AdminActivity;
import com.example.netflix_android.ViewModel.CategoryViewModel;
import com.example.netflix_android.ViewModel.CategoryViewModelFactory;
import java.util.List;

public class AdminCategoryAdapter extends RecyclerView.Adapter<AdminCategoryAdapter.CategoryViewHolder> {
    private Context context;
    private List<Category> categories;
    private CategoryViewModel categoryViewModel;

    public AdminCategoryAdapter(Context context, List<Category> categories, CategoryViewModel categoryViewModel) { // 🔺 Pass ViewModel
        this.context = context;
        this.categories = categories;
        this.categoryViewModel = categoryViewModel; // 🔺 Store ViewModel
    }

    @NonNull
    @Override
    public CategoryViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.item_category, parent, false);
        return new CategoryViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull CategoryViewHolder holder, int position) {
        Category category = categories.get(position);
        holder.categoryTitle.setText(category.getName());
        holder.categoryType.setText(category.isPromoted() ? "🌟 Promoted" : "📂 Regular");

        holder.editButton.setOnClickListener(v -> {
            Intent intent = new Intent(context, AddCategoryActivity.class); // 🔺 Use context
            intent.putExtra("category_id", category.getId());
            intent.putExtra("category_name", category.getName());
            intent.putExtra("category_promoted", category.isPromoted());
            ((AdminActivity) context).startActivityForResult(intent, 1); // 🔺 Ensure result is expected
        });

// ✅ Handle Delete Button Click
        holder.deleteButton.setOnClickListener(v -> {
            categoryViewModel.deleteCategory(category.getId()); // 🔺 Use ViewModel to delete
            Toast.makeText(context, "Category deleted successfully", Toast.LENGTH_SHORT).show();
        });

    }

    @Override
    public int getItemCount() {
        return categories.size();
    }

    public static class CategoryViewHolder extends RecyclerView.ViewHolder {
        TextView categoryTitle, categoryType;
        Button editButton, deleteButton;

        public CategoryViewHolder(@NonNull View itemView) {
            super(itemView);
            categoryTitle = itemView.findViewById(R.id.category_title);
            categoryType = itemView.findViewById(R.id.category_type);
            editButton = itemView.findViewById(R.id.button_edit);
            deleteButton = itemView.findViewById(R.id.button_delete);
        }
    }
}
