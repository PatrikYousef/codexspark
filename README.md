TODOLIST Calendar todolist_calender.cpp

🌟 Simple TODO Calendar is a minimalist and colorful C++ console application that helps you manage daily tasks by month. It features an intuitive text-based interface with calendar views, task addition, and task display functionalities — all neatly formatted with Unicode box characters and ANSI colors for enhanced readability.

Features

📅 View calendar days for each month in a clean, week-aligned layout
📌 Add tasks to any day of the selected month
📋 View all tasks stored for each month, grouped by day
🚪 Simple menu navigation with numbered options for adding/viewing tasks or exiting
✨ Color-coded UI using ANSI escape codes for a better user experience
🧹 Clear screen functionality for Windows and Unix-based terminals
How to Use

Build the program
Compile the source code with your favorite C++ compiler (supporting C++11 or later):
g++ -o todo_calendar todo_calendar.cpp
Run the program
./todo_calendar
Navigate the menu:
Select a number from the menu to add or view tasks by month.
When adding a task, enter the day of the month and then type your task description.
When viewing tasks, all saved tasks for that month are displayed by day.
Exit
Choose 0 to exit the application.
Dependencies

Standard C++ libraries (iostream, vector, string, iomanip, limits)
Terminal with ANSI color support recommended for the best visual experience (most Unix terminals, Windows Terminal, etc.)
Screenshots

╔════════════════════════════════════════════════════════════╗
                      🌟 SIMPLE TODO CALENDAR 🌟              
╚════════════════════════════════════════════════════════════╝

📌 =========== ADD TASK ===========
    1. January             2. February            3. March             4. April
    5. May                 6. June                7. July              8. August
    9. September          10. October            11. November         12. December

👁️  ========== VIEW TASKS ===========
    13. January           14. February           15. March            16. April
    17. May               18. June               19. July             20. August
    21. September         22. October            23. November         24. December

🚪 ============= EXIT ===============
    0. Exit
Code Highlights

Cross-platform screen clearing: Supports both Windows and Unix-like terminals.
Input validation: Ensures day input is valid for each month.
Clean, formatted output: Uses Unicode box-drawing characters and ANSI colors.
Task storage: Uses a vector of vectors of strings to store multiple tasks per day.
Future Improvements

Support for leap years (adjust February days dynamically)
Save tasks to a file and load on startup
Edit and delete tasks functionality
Enhanced navigation (jump between months, search tasks, etc.)
GUI or web-based version
License

This project is open-source and free to use. Feel free to modify and distribute!


## 🙌 Support & Contributions

If you found this project useful, fun, or inspiring — or if you're curious about my other C++ projects — please:

- ⭐ **Star** this repository to show your support  
- 👤 **Follow me** on GitHub for more creative C++ tools  
- 🍴 **Fork and contribute** — new features, ideas, or even small improvements are always welcome!  

> Let's build fun and helpful tools together! 😊

---


🙏 Thank You!
Proof of Impact & Value

Here’s a snapshot of the traffic my projects have received recently. This shows real engagement from a diverse audience — not just passive views, but active cloning and usage of my code.
	•	High number of views means many people are discovering and interested in my work.
	•	Significant clones, including unique cloners, demonstrate that users trust and use my projects practically.
	•	This kind of engagement is a strong indicator that my projects provide genuine value and meet real needs.

I’m proud of this progress and motivated to keep building tools that help developers
![image](https://github.com/user-attachments/assets/99c87235-007f-4660-8c57-8d1a08ab6e6d)

Over the past 14 days, my 12 GitHub projects have received:
	•	1691 views
	•	105 clones
	•	60 unique cloners

I’m truly grateful for the interest and support from all users and visitors. Your engagement motivates me to keep improving and creating valuable tools.

Thank you for checking out my projects, for starring, cloning, and contributing. Your support means a lot!





