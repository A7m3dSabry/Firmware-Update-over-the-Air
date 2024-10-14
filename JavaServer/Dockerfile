# Use a base image with OpenJDK installed (you can choose the JDK version you need)
FROM openjdk:17-jdk-slim

# Set the working directory inside the container
WORKDIR /app

# Set environment variables
ENV IMAGES_DIR=/app/images
ENV PORT=1234

# Copy the Java source code to the container
COPY ./src /app/src

# Compile the Java source code using javac
RUN javac -d out /app/src/Main.java

# Copy the Manifest file
COPY MANIFEST.MF out

# Create a JAR file from the compiled class files
RUN jar cfm server.jar ./out/MANIFEST.MF -C out .

# Cleaning
RUN rm -rf src out

# Expose the port that the server will run on
EXPOSE ${PORT}

# Command to run the server
CMD ["java", "-jar", "server.jar"]
