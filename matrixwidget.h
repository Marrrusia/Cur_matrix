
#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>        // Базовый класс для всех виджетов
#include <QGridLayout>    // Класс для компоновки виджетов в сетку
#include <QLineEdit>      // Класс для однострочного ввода текста
#include <QPushButton>    // Класс для кнопок
#include <QSpinBox>       // Класс для ввода целых чисел с кнопками увеличения/уменьшения
#include <QMessageBox>    // Класс для отображения диалоговых окон с сообщениями
#include <QDebug>         // Класс для отладочного вывода
#include <QTableView>     // Класс для отображения табличных данных
#include <QStandardItemModel> // Класс модели данных для QTableView
#include <QDialog>        // Базовый класс для диалоговых окон
#include <QVBoxLayout>    // Класс для вертикальной компоновки виджетов
#include <QLabel>         // Класс для отображения текста
#include <QHeaderView>    // Класс для отображения заголовков в QTableView
#include <QDoubleValidator> // Класс для валидации ввода чисел с плавающей точкой
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QColorDialog>
#include <random>


class MatrixWidget : public QWidget {
    Q_OBJECT // Макрос, необходимый для использования сигналов и слотов

public:
    MatrixWidget(QWidget *parent = nullptr); // Конструктор класса.
    ~MatrixWidget() override;              // Деструктор класса.

private slots:  // то что подключается к кнопкам
    void resizeMatrix();   // Слот для изменения размера матрицы
    void showSubmatrix();  // Слот для отображения подматрицы
    void showAllMatrix();  // Слот для отображения всей матрицы
    void saveMatrixToFile(); //сохранениие матрицы в файл
    void loadMatrixFromFile(); //загрузка матрицы из файла
    void saveSubmatrixToFile(); //сохранениие подматрицы в файл

    void clearAllMatrix(); // Слот для очистки всей матрицы
    void transposeMatrix(); // Слот для транспонирования матрицы
    void replaceElement(); // Слот для замены элементов
    void chooseHighlightColor(); // Слот для выбора цвета подсветки
    void highlightCells(); // Слот для подсветки ячеек
    void showRandomFillDialog(); // Слот для показа диалога рандомного заполнения
    void randomFillMatrix(double minVal, double maxVal); // Слот для рандомного заполнения матрицы

private:
    int rows = 3;             // Начальное количество строк матрицы
    int cols = 3;             // Начальное количество столбцов матрицы
    QVector<QVector<QLineEdit*>> matrix; // Матрица QLineEdit (двумерный вектор указателей на QLineEdit)

    QGridLayout* mainLayout;  // Главный макет для размещения виджетов
    QSpinBox* rowSpinBox;    // Спинбокс для выбора количества строк
    QSpinBox* colSpinBox;    // Спинбокс для выбора количества столбцов

    QPushButton* resizeButton; // Кнопка для изменения размера матрицы
    QPushButton* submatrixButton; // Кнопка для отображения подматрицы
    QPushButton* allMatrixButton; // Кнопка для отображения всей матрицы
    QPushButton* clearallmatrix; // Кнопка для очистки всей матрицы
    QPushButton* tmatrix; // Кнопка для транспонирования матрицы
    QPushButton* saveButton; // Кнопка для сохранения матрицы
    QPushButton* saveSubmatrixButton; // Кнопка для сохранения матрицы
    QPushButton* loadButton; // Кнопка для загрузки матрицы
    QPushButton* replaceButton; // Кнопка для замены элементов матрицы
    QPushButton* highlightButton; //Кнопка для поиска элементов матрицы
    QPushButton* randomFillButton; //Кнопка для рандомного заполнения матрицы


    QLineEdit* startRowEdit; // Поле ввода для указания начальной строки подматрицы
    QLineEdit* startColEdit; // Поле ввода для указания начального столбца подматрицы
    QLineEdit* subRowsEdit;  // Поле ввода для указания количества строк подматрицы
    QLineEdit* subColsEdit;  // Поле ввода для указания количества столбцов подматрицы

    void createMatrix(); // Создает матрицу QLineEdit
    void clearMatrix();  // Очищает существующую матрицу QLineEdit
    bool isValidSubmatrixParameters(int startRow, int startCol, int subRows, int subCols); // Проверяет допустимость параметров подматрицы


    void displayMatrixInTableView(const QVector<QVector<QString>>& data, const QString& title); // Отображает матрицу в таблице
signals:
    void colorChosen(const QColor& color);

};

#endif // MATRIXWIDGET_H
