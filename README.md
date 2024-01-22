# Coding Exercise

You are tasked with developing software to manage a space mining operation that extracts Helium-3 from lunar regolith. The operation consists of n-mining stations, each capable of handling one mining truck at a time. Mining trucks spend varying amounts of time mining, ranging from one to five hours. For the sake of this exercise, each truck has a random probability of mining in that range, per load. Mining trucks require 30 minutes to transition to an available mining station. Unloading a mining truck takes 5 minutes. Mining trucks should be directed to the first open station or if all stations are occupied, the station with the shortest queue. Trucks do not move queues after they enter them. Your objective is to create a simulation that can accept a configurable number of mining trucks and stations and then calculate statistics for each mining station and mining truck. The simulation should run faster than real-time. The simulation should represent 72 hours of continuous mining.

## Additional Details
* Please implement this project in C++. Please leverage OOP where it is appropriate.

### Goal:
The primary goal of this challenge is to demonstrate your professionalism as a software engineer. This process is designed to mimic a real-world scenario, including design, implementation, and design review. You will be evaluated based on various skills, including:
1. Communication: Clear and concise explanations of your code and design.
2. Documentation: Providing well-documented code and explanations.
3. Code Cleanliness: Writing clean and organized code.
4. Code Deployment: Demonstrating your ability to deploy and manage code.
5. Testing: Implementing appropriate testing strategies.