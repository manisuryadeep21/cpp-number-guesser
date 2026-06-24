#include <iostream>
#include <random>
#include <fstream>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    char play_again = 'y';
    int high_score = 999;

    std::ifstream infile("highscore.txt");
    if (infile.is_open())
    {
        infile >> high_score;
        infile.close();
    }

    while (play_again == 'y' || play_again == 'Y')
    {
        int max_range = 100;
        int choice = 0;

        std::cout << "\n===================================" << std::endl;
        std::cout << "---- Guess the Number Game v1.0 ----" << std::endl;
        std::cout << "===================================" << std::endl;

        while (true)
        {
            std::cout << "Select Difficulty:\n";
            std::cout << "1. Easy   (Range: 1 - 50)\n";
            std::cout << "2. Medium (Range: 1 - 100)\n";
            std::cout << "3. Hard   (Range: 1 - 500)\n";
            std::cout << "Enter choice (1-3): ";

            std::cin >> choice;

            if (std::cin.fail() || choice < 1 || choice > 3)
            {
                std::cout << "❌ Invalid choice! Please choose 1, 2, or 3.\n\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }

            break;
        }

        if (choice == 1)
            max_range = 50;
        else if (choice == 2)
            max_range = 100;
        else
            max_range = 500;

        std::uniform_int_distribution<int> distrib(1, max_range);

        int secret_number = distrib(gen);
        int guess = 0;
        int attempts = 0;

        std::cout << "\n-----------------------------------" << std::endl;

        if (high_score != 999)
        {
            std::cout << "[🏆 PERSISTENT HIGH SCORE: "
                      << high_score << " attempts]\n";
        }
        else
        {
            std::cout << "[🏆 PERSISTENT HIGH SCORE: No records yet]\n";
        }

        std::cout << "I picked a number between 1 and "
                  << max_range << ". Guess it!" << std::endl;

        std::cout << "-----------------------------------\n" << std::endl;

        while (true)
        {
            std::cout << "Enter your guess (1-" << max_range << "): ";
            std::cin >> guess;

            if (std::cin.fail())
            {
                std::cout << "⚠️ Invalid input! Please enter a valid number.\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
            }

            attempts++;

            if (guess == secret_number)
            {
                std::cout << "\n🎉 Congratulations! You guessed it in "
                          << attempts << " attempts!\n";

                if (attempts < high_score)
                {
                    high_score = attempts;
                    std::cout << "🔥 NEW HIGH SCORE SET!\n";

                    std::ofstream outfile("highscore.txt");

                    if (outfile.is_open())
                    {
                        outfile << high_score;
                        outfile.close();
                    }
                }

                break;
            }

            if (attempts == 3)
            {
                int midpoint = max_range / 2;

                std::cout << "\n💡 [HINT] You failed 3 times! Here is a clue:";

                if (secret_number <= midpoint)
                {
                    std::cout << " The number is between 1 and "
                              << midpoint << ".\n\n";
                }
                else
                {
                    std::cout << " The number is between "
                              << (midpoint + 1) << " and "
                              << max_range << ".\n\n";
                }
            }
            else if (attempts >= 4)
            {
                std::cout << "\n❌ Game Over! You couldn't guess it after the hint.\n";
                std::cout << "The correct answer was: "
                          << secret_number << "\n";
                break;
            }
            else
            {
                if (guess < secret_number)
                {
                    std::cout << "Too low! Try again.\n";
                }
                else
                {
                    std::cout << "Too high! Try again.\n";
                }
            }
        }

        std::cout << "\nDo you want to play again? (y/n): ";
        std::cin >> play_again;
    }

    std::cout << "\nThanks for playing! Goodbye.\n";

    return 0;
}
