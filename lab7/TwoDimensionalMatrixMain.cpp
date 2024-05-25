#include"../TwoDimensionalMatrix/Matrix.h"
int main() {
    setlocale(LC_ALL, "Russian");
    Matrix mat;
    int choice, wordNum, wordWrite, rowNumber, rowWrite;
    int firstWordIndex, secondWordIndex, resultIndex;
    string newWord, newRow, key, newWrd, searchWord;
    cout << "Выберите операцию:"
        "\n\t1. Просмотреть таблицу: "
        "\n\t2. Считать слово по номеру: "
        "\n\t3. Записать слово в таблицу: "
        "\n\t4. Считать адресный столбец: "
        "\n\t5. Записать адресный столбец в таблицу: "
        "\n\t6. Выполнить операцию f5 - записать второй аргумент на указанную позицию: "
        "\n\t7. Выполнить операцию f10 - записать отрицание второго аргумента на указанную позицию: "
        "\n\t8. Выполнить операцию f0 - записать число из нулей на указанную позицию: "
        "\n\t9. Выполнить операцию f15 - записать число из единиц на указанную позицию: "
        "\n\t10. Сложение полей в словах по заданному ключу: "
        "\n\t11. Поисковые операции(поиск по соответствию): "
        "\n\t12. Выйти из программы:\n"
        "Ваш выбор: ";
    cout << "\n";
    cin >> choice;
    cout << "\n";
    switch (choice) {
    case 1:
        mat.PrintMatrix();
        break;
    case 2:
        cout << "Введите номер слова:\n";
        cin >> wordNum;
        cout << "\n";
        mat.PrintWord(wordNum);
        break;
    case 3:
        cout << "Введите слово для записи:\n";
        cin >> newWord;
        cout << "\n";
        cout << "Введите номер столбца для записи слова:\n";
        cin >> wordWrite;
        cout << "\n";
        mat.getWord(newWord, wordWrite);
        cout << "\n";
        cout << "Слово записано в столбец " << wordWrite << "\n";
        break;
    case 4:
        cout << "Введите номер столбца:\n";
        cin >> rowNumber;
        cout << "\n";
        mat.PrintAddressRow(rowNumber);
        break;
    case 5:
        cout << "Введите адресный столбец для записи:\n";
        cin >> newRow;
        cout << "\n";
        cout << "Введмите номер столбца для записи столбца:\n";
        cin >> rowWrite;
        cout << "\n";
        mat.getAddressRow(newRow, rowWrite);
        break;
    case 6:
        cout << "Введите номер первого слова:\n";
        cin >> firstWordIndex;
        cout << "\n";
        cout << "Введите номер второго слова:\n";
        cin >> secondWordIndex;
        cout << "\n";
        cout << "Введите номер столбца, в который будет записан результат:\n";
        cin >> resultIndex;
        cout << "\n";
        mat.F5(firstWordIndex, secondWordIndex, resultIndex);
        break;
    case 7:
        cout << "Введите номер первого слова:\n";
        cin >> firstWordIndex;
        cout << "\n";
        cout << "Введите номер второго слова:\n";
        cin >> secondWordIndex;
        cout << "\n";
        cout << "Введите номер столбца, в который будет записан результат:\n";
        cin >> resultIndex;
        cout << "\n";
        mat.F10(firstWordIndex, secondWordIndex, resultIndex);
        break;
    case 8:
        cout << "Введите номер столбца для записи слова:\n";
        cin >> resultIndex;
        cout << "\n";
        mat.F0(resultIndex);
        break;
    case 9:
        cout << "Введите номер столбца для записи слова:\n";
        cin >> resultIndex;
        cout << "\n";
        mat.F15(resultIndex);
        break;
    case 10:
        cout << "Введите ключ для поиска слова:\n";
        cin >> key;
        cout << "\n";
        newWrd = mat.Search(key);
        mat.Summa(newWrd);
        break;
    case 11:
        cout << "Введите аргумент для поиска:\n";
        cin >> searchWord;
        cout << "\n";
        mat.SearchMatch(searchWord);
        break;
    case 12:
        cout << "Выбрано завершение программы.\n";
        return 0;
        break;
    }
    while (choice > 0 && choice < 12) {
        cout << endl;
        cout << "Выберите операцию:"
            "\n\t1. Просмотреть таблицу: "
            "\n\t2. Считать слово по номеру: "
            "\n\t3. Записать слово в таблицу: "
            "\n\t4. Считать адресный столбец: "
            "\n\t5. Записать адресный столбец в таблицу: "
            "\n\t6. Выполнить операцию f5 - записать второй аргумент на указанную позицию: "
            "\n\t7. Выполнить операцию f10 - записать отрицание второго аргумента на указанную позицию: "
            "\n\t8. Выполнить операцию f0 - записать число из нулей на указанную позицию: "
            "\n\t9. Выполнить операцию f15 - записать число из единиц на указанную позицию: "
            "\n\t10. Сложение полей в словах по заданному ключу: "
            "\n\t11. Поисковые операции(поиск по соответствию): "
            "\n\t12. Выйти из программы:\n"
            "Ваш выбор: ";
        cout << "\n";
        cin >> choice;
        cout << "\n";
        switch (choice) {
        case 1:
            mat.PrintMatrix();
            break;
        case 2:
            cout << "Введите номер слова:\n";
            cin >> wordNum;
            cout << "\n";
            mat.PrintWord(wordNum);
            break;
        case 3:
            cout << "Введите слово для записи:\n";
            cin >> newWord;
            cout << "\n";
            cout << "Введите номер столбца для записи слова:\n";
            cin >> wordWrite;
            cout << "\n";
            mat.getWord(newWord, wordWrite);
            cout << "\n";
            cout << "Слово записано в столбец " << wordWrite << "\n";
            break;
        case 4:
            cout << "Введите номер столбца:\n";
            cin >> rowNumber;
            cout << "\n";
            mat.PrintAddressRow(rowNumber);
            break;
        case 5:
            cout << "Введите адресный столбец для записи:\n";
            cin >> newRow;
            cout << "\n";
            cout << "Введите номер столбца для записи столбца:\n";
            cin >> rowWrite;
            cout << "\n";
            mat.getAddressRow(newRow, rowWrite);
            break;
        case 6:
            cout << "Введите номер первого слова:\n";
            cin >> firstWordIndex;
            cout << "\n";
            cout << "Введите номер второго слова:\n";
            cin >> secondWordIndex;
            cout << "\n";
            cout << "Введите номер столбца, в который будет записан результат:\n";
            cin >> resultIndex;
            cout << "\n";
            mat.F5(firstWordIndex, secondWordIndex, resultIndex);
            break;
        case 7:
            cout << "Введите номер первого слова:\n";
            cin >> firstWordIndex;
            cout << "\n";
            cout << "Введите номер второго слова:\n";
            cin >> secondWordIndex;
            cout << "\n";
            cout << "Введите номер столбца, в который будет записан результат:\n";
            cin >> resultIndex;
            cout << "\n";
            mat.F10(firstWordIndex, secondWordIndex, resultIndex);
            break;
        case 8:
            cout << "Введите номер столбца для записи слова:\n";
            cin >> resultIndex;
            cout << "\n";
            mat.F0(resultIndex);
            break;
        case 9:
            cout << "Введите номер столбца для записи слова:\n";
            cin >> resultIndex;
            cout << "\n";
            mat.F15(resultIndex);
            break;
        case 10:
            cout << "Введите ключ для поиска слова:\n";
            cin >> key;
            cout << "\n";
            newWrd = mat.Search(key);
            mat.Summa(newWrd);
            break;
        case 11:
            cout << "Введите аргумент для поиска:\n";
            cin >> searchWord;
            cout << "\n";
            mat.SearchMatch(searchWord);
            break;
        case 12:
            cout << "Выбрано завершение программы.\n";
            return 0;
            break;
            cin >> choice;
        }
    }
    return 0;
}
