/**
 * Саженов К.С.
 * М8О-208Б-19
 * https://github.com/sakost/oop_excercise_05
 *
 * Вариант 30:
 * Пятиугольник. Динамический массив
 **/

#include <iostream>

#include "custom_vector.h"
#include "pentagon.h"

void help(std::ostream &out) {
    out << "0\t-\tHelp(this) message\n";
    out << "1\t-\tPush back figure\n";
    out << "2\t-\tInsert figure(by iterator)\n";
    out << "3\t-\tPop back figure\n";
    out << "4\t-\tErase figure(by iterator)\n";
    out << "5\t-\tPrint\n";
    out << "6\t-\tI-ths figure\n";
    out << "7\t-\tBack\n";
    out << "8\t-\tCount_if\n";
    out << "9\t-\tExit\n";
}


int main() {
    CustomVector<Pentagon<int>> vec;

    typename Pentagon<int>::area_type area = 0;
    int cmd;
    help(std::cout);

    while (true) {
        std::cout << ">>> ";
        std::cout.flush();
        std::cin >> cmd;
        switch (cmd) {
            case 0: {
                help(std::cout);
                continue;
            }
            case 1: {
                std::cout << "Print side of figure:" << std::endl;
                Pentagon<int> pen;
                try {
                    std::cin >> pen;
                    vec.push_back(pen);
                } catch (std::exception &err) {
                    std::cout << err.what() << std::endl;
                    break;
                }
                std::cout << "Figure successfully added!" << std::endl;
            }
                break;
            case 2: {
                std::cout << "Print an index where to insert figure:" << std::endl;
                int index;
                std::cin >> index;
                std::cout << "Print side of figure:" << std::endl;
                Pentagon<int> pen;
                try {
                    std::cin >> pen;
                    vec.insert(std::next(vec.begin(), index), pen);
                } catch (std::exception &err) {
                    std::cout << err.what() << std::endl;
                    break;
                }
                std::cout << "Figure successfully added!" << std::endl;
            }
                break;
            case 3: {
                std::cout << "Ok. Deleting last element..." << std::endl;
                try {
                    vec.pop_back();
                } catch (std::exception &err) {
                    std::cout << err.what() << std::endl;
                    break;
                }
                std::cout << "Figure successfully deleted!" << std::endl;
                break;
            }
            case 4: {
                std::cout << "Print an index of figure which should be deleted:" << std::endl;
                int index;
                std::cin >> index;
                CustomVector<Pentagon<int>>::iterator it;
                try {
                    it = std::next(vec.begin(), index);
                    vec.erase(it);
                } catch (std::exception &err) {
                    std::cout << err.what() << std::endl;
                    break;
                }
                std::cout << "Figure successfully erased!" << std::endl;
            }
                break;
            case 5: {
                std::cout << "All figures:" << std::endl;
                std::for_each(vec.begin(), vec.end(), [](auto &pen) {
                    std::cout << pen << std::endl;
                });
            }
                break;
            case 6: {
                std::cout << "Print an index of figure which should be printed:" << std::endl;
                int index;
                std::cin >> index;
                try {
                    std::cout << vec.at(index) << std::endl;
                } catch (std::exception &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "Last figure:" << std::endl;
                try {
                    std::cout << vec.back() << std::endl;
                } catch (std::exception &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 8: {
                std::cout << "Type the threshold for areas:" << std::endl;
                std::cin >> area;
                std::size_t ans = std::count_if(vec.begin(), vec.end(), [area](Pentagon<int> &pen) {
                    return pen.area() < area;
                });
                std::cout << "Count of objects of less than " << area << " area is " << ans << std::endl;
                break;
            }
            case 9: {
                std::cout << "Bye!" << std::endl;
                return 0;
            }
            default: {
                std::cout << "Unknown command. To get all available commands type 0 and press enter" << std::endl;
                continue;
            }
        }

    }
}
