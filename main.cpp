#include "image.h" //подключаем заголовочный файл
void print_menu(); //"Меню"
int get_variant(int count, int& variant); //Выбранное пользователем действие
int main()
{
    int variant=0;
    do {
        print_menu();
        variant = get_variant(11, variant);
        switch (variant)
        {
        case 1:
        {
            string name; //название фото
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); //создание объекта класса Image
            int w1 = 0;
            cout << "Select the height of the first photo (it should be less than the entire height "<<img.getWidth() << " ): ";
            cin >> w1;
            img.SaveVerticalSelect(w1, "Left_"+name, "Right_"+name);
            break;
        }
        case 2:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name);
            int h1 = 0;
            cout << "Select the width of the first photo (it should be less than the entire width " << img.getHeight() << " ): ";
            cin >> h1;
            img.SaveHorisontalSelect(h1, "Lower_"+name, "Upper_"+name);
            break;
        }
        case 3:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "Grey_" + name;
            img.Grey(name);
            break;
        }
        case 4:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "Sepia_" + name;
            img.Sepia(name);
            break;
        }
        case 5:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "Inverted_" + name;
            img.Invert(name);
            break;
        }
        case 6:
        {
            string name; int force;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "Blur_" + name;
            cout << "Enter the blur force (from 1 to 10): ";
            cin >> force;
            img.blur(force);
            img.Save(name);
            break;
        }
        case 7:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "fo_flip_" + name;
            img.Flip(name);
            break;
        }
        case 8:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "to_right_" + name;
            img.turn_right(name);
            break;
        }
        case 9:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "to_left_" + name;
            img.turn_left(name);
            break;
        }
        case 10:
        {
            string name;
            cout << "Enter BMP file name (without format): ";
            cin >> name; name = name + ".bmp";
            Image img(name); name = "mirred_" + name;
            img.Mirror(name);
            break;
        }
        if (variant !=11)
            system("pause");
        }
    } while (variant !=11);
	return 0;
}
void print_menu() {
    system("cls");  // очищаем экран
    cout << "What do you want to do?" << endl;
    cout << "1. Split the photo vertically" << endl;
    cout << "2. split the photo horizontally" << endl;
    cout << "3. Image with gray shades" << endl;
    cout << "4. Image in sepia shades" << endl;
    cout << "5. Invert image" << endl; 
    cout << "6. Blur image" << endl;
    cout << "7. Flip the photo 180 degrees" << endl;
    cout << "8. Flip the photo 90 degrees to the right" << endl;
    cout << "9. Flip the photo 90 degrees to the left" << endl;
    cout << "10 Mirror the image" << endl;
    cout << "11. Exit" << endl;
    cout << ">  ";
}
int get_variant(int count, int& variant) {
    cin >> variant;
    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (variant < 1 || variant > count) {
        cout << "Incorrect input. Try again: "; // выводим сообщение об ошибке
        cin >> variant;
    }
    return variant;
}