# Use Node.js LTS as base image
FROM node:18


# Copy package.json and install dependencies
COPY package*.json ./
RUN npm install

# Copy the rest of the application code
COPY . .

# Expose the port
EXPOSE ${PORT}

# Start the app
CMD ["npm", "start"]
