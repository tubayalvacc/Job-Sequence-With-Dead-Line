#include <iostream> // Include input-output stream library
#include <cstring>  // Include C-string library for string operations

#define MAX 100 // Define maximum number of slots

// Structure to store job details
struct Job {
    char id[5]; // Job ID
    int deadline; // Deadline of the job
    int profit; // Profit if the job is completed before or on the deadline
};

// Function to find the minimum value between two integers
int minValue(int x, int y) {
    return (x < y) ? x : y; // Return the smaller value
}

// Function to schedule jobs to maximize profit
void jobSequencing(Job jobs[], int n) {
    int i, j, k, maxProfit = 0;
    int timeSlot[MAX]; // Array to keep track of free time slots
    int filledTimeSlot = 0; // Counter for filled time slots
    int dMax = 0; // Maximum deadline

    // Find the maximum deadline
    for (i = 0; i < n; i++) {
        if (jobs[i].deadline > dMax) {
            dMax = jobs[i].deadline;
        }
    }
    std::cout << "\nTotal time slots: " << dMax << std::endl;

    // Initialize all time slots to -1 (free)
    for (i = 1; i <= dMax; i++) {
        timeSlot[i] = -1;
    }

    // Iterate over each job in descending order of profit
    for (i = 0; i < n; i++) {
        k = minValue(dMax, jobs[i].deadline); // Find the latest available slot for the job

        // Find a free slot for this job
        while (k >= 1) {
            if (timeSlot[k] == -1) { // If the slot is free
                timeSlot[k] = i; // Assign this job to the slot
                filledTimeSlot++; // Increment filled slot count
                break; // Move to the next job
            }
            k--; // Try the previous slot
        }
        if (filledTimeSlot == dMax) { // If all slots are filled
            break; // No need to schedule more jobs
        }
    }

    std::cout << "\nJobs DONE! ";
    for (i = 1; i <= dMax; i++) {
        if (timeSlot[i] != -1) { // Print only filled slots
            std::cout << "\nJob " << jobs[timeSlot[i]].id << " at time " << i;
            maxProfit += jobs[timeSlot[i]].profit; // Calculate the total profit
        }
    }
    std::cout << "\nTotal Benefit: " << maxProfit << std::endl;
}

// Main function
int main() {
    int i, j, n;
    Job jobs[5]; // Array to store jobs
    std::cout << "\nEnter the number of Jobs: ";
    std::cin >> n;

    // Input job details
    for (i = 0; i < n; i++) {
        std::cout << "\nEnter the job ID: ";
        std::cin >> jobs[i].id;
        std::cout << "Enter the profit: ";
        std::cin >> jobs[i].profit;
        std::cout << "Enter the deadline: ";
        std::cin >> jobs[i].deadline;
    }

    // Sort jobs based on profit in descending order
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }

    std::cout << "\nJob\tProfit\tDeadline\n";
    std::cout << "-----------------------------";
    for (i = 0; i < n; i++) {
        std::cout << "\n" << jobs[i].id << "\t" << jobs[i].profit << "\t" << jobs[i].deadline;
    }

    jobSequencing(jobs, n); // Call job sequencing function
    getchar(); // Wait for user input before closing
    return 0; // Return 0 to indicate successful execution
}
