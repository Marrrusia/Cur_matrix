#include "matrixwidget.h"
#include <QVector>
#include <QString>

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent) {
    // основной макет для размещения виджетов
    mainLayout = new QGridLayout(this);

    // Создаем QSpinBox для выбора количества строк
    rowSpinBox = new QSpinBox();
    rowSpinBox->setRange(1, 100); // Устанавливаем диапазон значений от 1 до 100
    rowSpinBox->setValue(rows);   // Устанавливаем начальное значение

    // Создаем QSpinBox для выбора количества столбцов
    colSpinBox = new QSpinBox();
    colSpinBox->setRange(1, 100); // Устанавливаем диапазон значений от 1 до 100
    colSpinBox->setValue(cols);   // Устанавливаем начальное значение

    // Создаем кнопку для изменения размера матрицы
    resizeButton = new QPushButton("Изменить размер матрицы");

    // ---- Подматрица ----
    // Создаем QLineEdit для ввода начальной строки подматрицы
    startRowEdit = new QLineEdit();
    startRowEdit->setPlaceholderText("Начальная строка"); // Устанавливаем текст-подсказку
    startRowEdit->setValidator(new QIntValidator(this)); // Разрешаем ввод только целых чисел

    // Создаем QLineEdit для ввода начального столбца подматрицы
    startColEdit = new QLineEdit();
    startColEdit->setPlaceholderText("Начальный столбец");
    startColEdit->setValidator(new QIntValidator(this));

    // Создаем QLineEdit для ввода количества строк подматрицы
    subRowsEdit = new QLineEdit();
    subRowsEdit->setPlaceholderText("Количество строк");
    subRowsEdit->setValidator(new QIntValidator(this));

    // Создаем QLineEdit для ввода количества столбцов подматрицы
    subColsEdit = new QLineEdit();
    subColsEdit->setPlaceholderText("Количество столбцов");
    subColsEdit->setValidator(new QIntValidator(this));
    // --------------------

    // Создаем кнопки:
    submatrixButton = new QPushButton("Вывести подматрицу");    //для вывода подматрицы
    allMatrixButton = new QPushButton("Вывести всю матрицу");   //для вывода всей матрицы
    clearallmatrix = new QPushButton("Очистить всю матрицу");   //для очистки всей матрицы
    tmatrix= new QPushButton("Транспонировать матрицу");      //для транспонирования матрицы
    saveButton = new QPushButton("Сохранить матрицу в файл");        //для сохранения матрицы
    saveSubmatrixButton = new QPushButton("Сохранить подматрицу в файл");   //для сохранения матрицы
    loadButton = new QPushButton("Загрузить матрицу из файла");       //для загрузки матрицы
    replaceButton = new QPushButton("Замена элемента(ов)");
    highlightButton = new QPushButton("Поиск ячеек");
    randomFillButton = new QPushButton("Заполнить случайными числами");

    // Добавляем виджеты в основной макет
    mainLayout->addWidget(new QLabel("Количество строк:", this), 1, 0);    // Выбор количесива строк
    mainLayout->addWidget(rowSpinBox, 1, 1);                    // Спинбокс для строк
    mainLayout->addWidget(new QLabel("Количество столбцов:", this), 2, 0); // Выбор количества столбцов
    mainLayout->addWidget(colSpinBox, 2, 1);                    // Спинбокс для столбцов

    mainLayout->addWidget(resizeButton, 1, 2, 1, 1);             // Кнопка изменения размера

    mainLayout->addWidget(new QLabel("Начальная строка подматрицы:", this), 3, 0);
    mainLayout->addWidget(startRowEdit, 3, 1);                                  // Поле ввода начальной строки
    mainLayout->addWidget(new QLabel("Начальный столбец подматрицы:", this), 4, 0);
    mainLayout->addWidget(startColEdit, 4, 1);                                  // Поле ввода начального столбца
    mainLayout->addWidget(new QLabel("Количество строк подматрицы:", this), 5, 0);
    mainLayout->addWidget(subRowsEdit, 5, 1);                                  // Поле ввода количества строк
    mainLayout->addWidget(new QLabel("Количество столбцов подматрицы:", this), 6, 0);
    mainLayout->addWidget(subColsEdit, 6, 1);                                  // Поле ввода количества столбцов

    mainLayout->addWidget(submatrixButton, 8, 0, 1, 1);      // Кнопка вывода подматрицы
    mainLayout->addWidget(allMatrixButton, 7, 0, 1, 1);      // Кнопка вывода всей матрицы
    mainLayout->addWidget(clearallmatrix, 9, 0, 1, 1);       // Кнопка очистки всей матрицы

    mainLayout->addWidget(saveButton, 7, 1, 1, 1);           //загрузка матрицы
    mainLayout->addWidget(saveSubmatrixButton, 8, 1, 1, 1);           //загрузка подматрицы
    mainLayout->addWidget(loadButton, 9, 1, 1, 1);           // Кнопка сохранения матрицы

    mainLayout->addWidget(tmatrix, 7, 2, 1, 1);           // Кнопка транспонирования матрицы
    mainLayout->addWidget(replaceButton, 8, 2, 1, 1);     // Кнопка замены элементов
    mainLayout->addWidget(highlightButton, 9, 2, 1, 1);     // Кнопка поиска элементов

    mainLayout->addWidget(randomFillButton, 2, 2, 1, 1);     // Кнопка поиска элементов

    // Соединяем сигналы и слоты
    connect(resizeButton, &QPushButton::clicked, this, &MatrixWidget::resizeMatrix);       // При нажатии на кнопку resizeButton вызывается слот resizeMatrix
    connect(submatrixButton, &QPushButton::clicked, this, &MatrixWidget::showSubmatrix);
    connect(allMatrixButton, &QPushButton::clicked, this, &MatrixWidget::showAllMatrix);
    connect(clearallmatrix, &QPushButton::clicked, this, &MatrixWidget::clearAllMatrix);
    connect(tmatrix, &QPushButton::clicked, this, &MatrixWidget::transposeMatrix);
    connect(saveButton, &QPushButton::clicked, this, &MatrixWidget::saveMatrixToFile);
    connect(loadButton, &QPushButton::clicked, this, &MatrixWidget::loadMatrixFromFile);
    connect(saveSubmatrixButton, &QPushButton::clicked, this, &MatrixWidget::saveSubmatrixToFile);
    connect(replaceButton, &QPushButton::clicked, this, &MatrixWidget::replaceElement);
    connect(highlightButton, &QPushButton::clicked, this, &MatrixWidget::highlightCells);
    connect(randomFillButton, &QPushButton::clicked, this, &MatrixWidget::showRandomFillDialog);

    // Создаем матрицу из QLineEdit
    createMatrix();
}

MatrixWidget::~MatrixWidget() { //деструктор
    clearMatrix();
}

// Создание матрицы
void MatrixWidget::createMatrix() {
    // Изменяем размер вектора matrix, чтобы он вмещал rows строк
    matrix.resize(rows);

    for (int i = 0; i < rows; ++i) {
        // Изменяем размер каждой строки (вектора) matrix[i], чтобы она вмещала cols столбцов
        matrix[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            // Создаем новый QLineEdit объект и присваиваем его элементу matrix[i][j]
            matrix[i][j] = new QLineEdit();
            matrix[i][j]->setAlignment(Qt::AlignCenter); //выравнивание по центру
            matrix[i][j]->setMinimumWidth(200); //минимальная ширина QLineEdit

            // Добавляем QLineEdit в основной макет (mainLayout)
            mainLayout->addWidget(matrix[i][j], i + 10, j);

            QDoubleValidator *validator = new QDoubleValidator(this); // для проверки ввода чисел

            // Устанавливаем валидатор, чтобы пользователь мог вводить только числа
            matrix[i][j]->setValidator(validator);
        }
    }
}

void MatrixWidget::clearAllMatrix() {
    //  Проверяем, что матрица вообще создана
    if (matrix.isEmpty()) {
        return; // Ничего не делаем, если матрица пуста
    }

    //  Перебираем все QLineEdit и устанавливаем пустой текст
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j]) {
                matrix[i][j]->setText(""); // Устанавливаем пустой текст
            }
        }
    }
}

//Очистка матрицы
void MatrixWidget::clearMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Удаляем виджет matrix[i][j] из макета mainLayout
            mainLayout->removeWidget(matrix[i][j]);
            // Удаляем QLineEdit объект, на который указывает matrix[i][j]
            delete matrix[i][j];
        }
        matrix[i].clear();
    }
    matrix.clear();
}


// Изменение размера матрицы с сохранением данных
void MatrixWidget::resizeMatrix() {
    // oldData - для хранения текущих значений из QLineEdit
    QVector<QVector<QString>>oldData(rows, QVector<QString>(cols));

    // Заполняем oldData значениями из текущих QLineEdit
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            oldData[i][j] = matrix[i][j]->text();
        }
    }

    clearMatrix(); // Очистка старой матрицы

    // Получаем новые размеры матрицы
    int newRows = rowSpinBox->value();
    int newCols = colSpinBox->value();
    // Обновляем переменные rows и cols класса MatrixWidget
    rows = newRows;
    cols = newCols;

    createMatrix();// Создаем новую матрицу

    // Переносим данные из временной матрицы oldData в новую матрицу.
    // min - перенос только тех данных, которые помещаются в новую матрицу (в случае, если новый размер меньше старого)
    for (int i = 0; i < std::min(rows, (int)oldData.size()); ++i) {
        for (int j = 0; j < std::min(cols, (int)oldData[0].size()); ++j) {
            matrix[i][j]->setText(oldData[i][j]);
        }
    }
}

//Проверка введенных пользователем данных о подматрице
bool MatrixWidget::isValidSubmatrixParameters(int startRow, int startCol, int subRows, int subCols) {

    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols) {
        QMessageBox::warning(this, "Ошибка", "Некорректные значения начала строки или столбца.");
        return false;
    }

    if (startRow + subRows > rows || startCol + subCols > cols) {
        QMessageBox::warning(this, "Ошибка", "Подматрица выходит за границы матрицы.");
        return false;
    }

    if (subRows <= 0 || subCols <= 0) {
        QMessageBox::warning(this, "Ошибка", "Размеры подматрицы должны быть больше нуля.");
        return false;
    }

    return true;
}

// Выводит введенную пользователем матрицу в виде таблицы
void MatrixWidget::displayMatrixInTableView(const QVector<QVector<QString>>& data, const QString& title) {
    // Проверяем, что все ячейки заполнены данными
    for (const auto& row : data) {
        for (const auto& cell : row) {
            if (cell.isEmpty()) {
                QMessageBox::warning(this, "Предупреждение", "Таблица содержит пустые ячейки и не может быть отображена.");
                return;
            }
        }
    }

    // Создаем диалоговое окно для отображения таблицы
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle(title); // Устанавливаем заголовок окна

    // Создаем вертикальный макет для размещения виджетов в диалоговом окне
    QVBoxLayout* dialogLayout = new QVBoxLayout(dialog);

    // Создаем QTableView для отображения табличных данных
    QTableView* tableView = new QTableView(dialog);

    // Создаем QStandardItemModel для хранения данных таблицы, указываем количество строк и столбцов
    QStandardItemModel* model = new QStandardItemModel(data.size(), data[0].size(), dialog);

    // Заполняем модель данными
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[0].size(); ++j) {
            QStandardItem* item = new QStandardItem(data[i][j]);
            item->setTextAlignment(Qt::AlignCenter);
            // Устанавливаем элемент в модель
            model->setItem(i, j, item);
        }
    }

    // Устанавливаем модель для QTableView
    tableView->setModel(model);
    // размер столбцов и строк по содержимому
    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();

    //Настройка внешнего вида заголовков
    QHeaderView *verticalHeader = tableView->verticalHeader();
    QHeaderView *horizontalHeader = tableView->horizontalHeader();
    horizontalHeader->setStyleSheet("QHeaderView::section { background-color: pink; color: black;}");
    verticalHeader->setStyleSheet("QHeaderView::section { background-color: pink; color: black; }");

    // Добавляем QTableView в макет диалогового окна
    dialogLayout->addWidget(tableView);

    // Создаем QLabel для отображения заголовка таблицы
    QLabel* titleLabel = new QLabel(title, dialog);
    titleLabel->setAlignment(Qt::AlignCenter); // текст в центре

    // Вставляем titleLabel в макет перед QTableView (в позицию 0)
    dialogLayout->insertWidget(0, titleLabel);

    // Устанавливаем макет для диалогового окна
    dialog->setLayout(dialogLayout);

    dialog->exec(); //запрет взаимодействия с другими окнами
    delete dialog; //удаление диалогового окна
}

//Вывод подматрицы на экран и проверкина корректность
void MatrixWidget::showSubmatrix() {
    bool ok;
    // Получение параметров подматрицы из полей ввода и проверка на корректность
    int startRow = startRowEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод начальной строки."); return; }

    int startCol = startColEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод начального столбца."); return; }

    int subRows = subRowsEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод количества строк."); return; }

    int subCols = subColsEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод количества столбцов."); return; }

    startRow--; startCol--;
    // Вызываем функцию для проверки, являются ли введенные параметры допустимыми
    if (!isValidSubmatrixParameters(startRow, startCol, subRows, subCols)) return;

    QVector<QVector<QString>> submatrixData(subRows, QVector<QString>(subCols)); //вектор для хранения данных подматрицы
    // Заполняем вектор значениями из QLineEdit основной матрицы, соответствующими подматрице
    for (int i = 0; i < subRows; ++i) {
        for (int j = 0; j < subCols; ++j) {
            submatrixData[i][j] = matrix[startRow + i][startCol + j]->text();
        }
    }
    displayMatrixInTableView(submatrixData, "Подматрица"); //вывод таблицы на экран
}

//Вывод всей матрицы на экран
void MatrixWidget::showAllMatrix() {
    QVector<QVector<QString>> allMatrixData(rows, QVector<QString>(cols)); //вектор для хранения данных матрицы
    // Заполняем вектор значениями из QLineEdit основной матрицы
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            allMatrixData[i][j] = matrix[i][j]->text();
        }
    }
    displayMatrixInTableView(allMatrixData, "Матрица"); //вывод таблицы на экран
}

void MatrixWidget::saveMatrixToFile() {
    //Проверка на наличие пустых ячеек
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j]->text().isEmpty()) {
                QMessageBox::warning(this, "Предупреждение", "Невозможно сохранить матрицу с пустыми ячейками.");
                return; // Прекращаем сохранение
            }
        }
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить матрицу", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return; // Пользователь отменил сохранение
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);

    // Сохраняем размеры матрицы в файл
    out << rows << " " << cols << "\n";

    // Сохраняем данные матрицы
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            out << matrix[i][j]->text();
            if (j < cols - 1) {
                out << " "; // Разделитель между элементами в строке
            }
        }
        out << "\n"; // Переход на новую строку
    }

    file.close();
    QMessageBox::information(this, "Информация", "Матрица успешно сохранена.");
}


void MatrixWidget::loadMatrixFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить матрицу", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return; // Пользователь отменил загрузку
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    QTextStream in(&file);

    int newRows, newCols;

    // Читаем размеры матрицы из файла
    in >> newRows >> newCols;  // Сначала читаем данные, потом проверяем состояние

    if (in.status() != QTextStream::Ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат файла: не удалось прочитать размеры матрицы.");
        file.close();
        return;
    }


    // Очищаем старую матрицу
    clearMatrix();

    // Обновляем размеры матрицы
    rows = newRows;
    cols = newCols;

    // Создаем новую матрицу
    createMatrix();

    // Читаем данные матрицы из файла
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QString value;
            in >> value; // Читаем значение, потом проверяем состояние

            if (in.status() != QTextStream::Ok) {
                QMessageBox::warning(this, "Ошибка", "Некорректный формат файла: не удалось прочитать данные матрицы.");
                file.close();
                clearMatrix(); // Очищаем, если загрузка не удалась
                createMatrix(); // Создаем матрицу с изначальным размером
                return;
            }
            matrix[i][j]->setText(value);
        }
    }

    file.close();
    QMessageBox::information(this, "Информация", "Матрица успешно загружена.");
}


void MatrixWidget::saveSubmatrixToFile() {
    bool ok;

    // Получаем параметры подматрицы из QLineEdit
    int startRow = startRowEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод начальной строки."); return; }

    int startCol = startColEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод начального столбца."); return; }

    int subRows = subRowsEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод количества строк."); return; }

    int subCols = subColsEdit->text().toInt(&ok);
    if (!ok) { QMessageBox::warning(this, "Ошибка", "Некорректный ввод количества столбцов."); return; }

    startRow -= startRow; startCol -= startCol;
    // Проверяем параметры подматрицы на валидность
    if (!isValidSubmatrixParameters(startRow, startCol, subRows, subCols)) return;

    // Проверка на наличие пустых ячеек в подматрице
    for (int i = 0; i < subRows; ++i) {
        for (int j = 0; j < subCols; ++j) {
            if (matrix[startRow + i][startCol + j]->text().isEmpty()) {
                QMessageBox::warning(this, "Предупреждение", "Невозможно сохранить подматрицу с пустыми ячейками.");
                return; // Прекращаем сохранение
            }
        }
    }


    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить подматрицу", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) {
        return; // Пользователь отменил сохранение
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);

    // Сохраняем размеры подматрицы в файл
    out << subRows << " " << subCols << "\n";

    // Сохраняем данные подматрицы
    for (int i = 0; i < subRows; ++i) {
        for (int j = 0; j < subCols; ++j) {
            out << matrix[startRow + i][startCol + j]->text();
            if (j < subCols - 1) {
                out << " "; // Разделитель между элементами в строке
            }
        }
        out << "\n"; // Переход на новую строку
    }

    file.close();
    QMessageBox::information(this, "Информация", "Подматрица успешно сохранена.");
}


void MatrixWidget::transposeMatrix() {
    //Создание новой матрицы с инвертированными размерами
    QVector<QVector<QString>> transposedData(cols, QVector<QString>(rows));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposedData[j][i] = matrix[i][j]->text();
        }
    }

    //Очистка старой матрицы
    clearMatrix();

    //Инвертируем размеры
    int temp = rows;
    rows = cols;
    cols = temp;

    //Создание новой транспонированной матрицы
    createMatrix();

    //Заполняем новыми значениями
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j]->setText(transposedData[i][j]);
        }
    }
}

//Заменяет все элементы с заданным значением на другое значение.
void MatrixWidget::replaceElement() {
    QDialog dialog(this);
    dialog.setWindowTitle("Заменить элемент");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Поля ввода для значения, которое нужно заменить, и нового значения
    QLabel* findLabel = new QLabel("Найти:", &dialog);
    QLineEdit* findEdit = new QLineEdit(&dialog);
    layout->addWidget(findLabel);
    layout->addWidget(findEdit);

    QLabel* replaceLabel = new QLabel("Заменить на:", &dialog);
    QLineEdit* replaceEdit = new QLineEdit(&dialog);
    layout->addWidget(replaceLabel);
    layout->addWidget(replaceEdit);

    // Кнопки "OK" и "Отмена"
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Обработка результатов диалога
    if (dialog.exec() == QDialog::Accepted) {
        QString findValue = findEdit->text();
        QString replaceValue = replaceEdit->text();

        // Заменяем все элементы с заданным значением
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j]->text() == findValue) {
                    matrix[i][j]->setText(replaceValue);
                }
            }
        }

        QMessageBox::information(this, "Информация", "Замена элементов выполнена.");
    }
}

//Поиск элементов
void MatrixWidget::highlightCells() {
    QDialog dialog(this);
    dialog.setWindowTitle("Подсветка ячеек");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Поля ввода для значения и цвета подсветки
    QLabel* valueLabel = new QLabel("Значение:", &dialog);
    QLineEdit* valueEdit = new QLineEdit(&dialog);
    layout->addWidget(valueLabel);
    layout->addWidget(valueEdit);

    QLabel* colorLabel = new QLabel("Цвет:", &dialog);
    QPushButton* colorButton = new QPushButton("Выбрать цвет", &dialog);
    layout->addWidget(colorLabel);
    layout->addWidget(colorButton);

    // Кнопки "OK" и "Отмена"
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(colorButton, &QPushButton::clicked, this, &MatrixWidget::chooseHighlightColor);

    // Сохраняем выбранный цвет
    QColor selectedColor = Qt::white;  // Цвет по умолчанию

    connect(this, &MatrixWidget::colorChosen, this, [&selectedColor](const QColor& color) {
        selectedColor = color;
    });

    // Обработка результатов
    if (dialog.exec() == QDialog::Accepted) {
        QString valueToHighlight = valueEdit->text();

        // Подсветка ячеек с заданным значением
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j]->text() == valueToHighlight) {
                    QPalette palette = matrix[i][j]->palette();
                    palette.setColor(QPalette::Base, selectedColor);  // Устанавливаем цвет фона
                    matrix[i][j]->setPalette(palette);
                } else {
                    // Сбрасываем цвет, если ячейка не соответствует значению
                    QPalette palette = matrix[i][j]->palette();
                    palette.setColor(QPalette::Base, QColor(255,255,255)); // Возвращаем белый цвет
                    matrix[i][j]->setPalette(palette);
                }
            }
        }

        QMessageBox::information(this, "Информация", "Поиск ячеек выполнен.");
    }
}

void MatrixWidget::chooseHighlightColor() {
    QColor color = QColorDialog::getColor(Qt::yellow, this, "Выберите цвет подсветки");
    if (color.isValid()) {
        emit colorChosen(color);
    }
}

void MatrixWidget::randomFillMatrix(double minVal, double maxVal) {
    // Создаем генератор случайных чисел
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Определяем распределение случайных чисел (равномерное в диапазоне [minVal, maxVal])
    std::uniform_real_distribution<> distrib(minVal, maxVal);

    // Заполняем матрицу случайными числами
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double randomValue = distrib(gen);
            matrix[i][j]->setText(QString::number(randomValue));
        }
    }
}

void MatrixWidget::showRandomFillDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Заполнить случайными числами");

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // Поля ввода для минимального и максимального значений
    QLabel* minLabel = new QLabel("Минимальное значение:", &dialog);
    QLineEdit* minEdit = new QLineEdit(&dialog);
    minEdit->setValidator(new QDoubleValidator(&dialog)); // Валидация для дробных чисел
    layout->addWidget(minLabel);
    layout->addWidget(minEdit);

    QLabel* maxLabel = new QLabel("Максимальное значение:", &dialog);
    QLineEdit* maxEdit = new QLineEdit(&dialog);
    maxEdit->setValidator(new QDoubleValidator(&dialog)); // Валидация для дробных чисел
    layout->addWidget(maxLabel);
    layout->addWidget(maxEdit);

    // Кнопки "OK" и "Отмена"
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // Обработка результатов
    if (dialog.exec() == QDialog::Accepted) {
        bool okMin, okMax;
        double minVal = minEdit->text().toDouble(&okMin);
        double maxVal = maxEdit->text().toDouble(&okMax);

        if (!okMin || !okMax) {
            QMessageBox::warning(this, "Ошибка", "Некорректный ввод минимального или максимального значения.");
            return;
        }

        if (minVal >= maxVal) {
            QMessageBox::warning(this, "Ошибка", "Минимальное значение должно быть меньше максимального.");
            return;
        }

        randomFillMatrix(minVal, maxVal);
    }
}
