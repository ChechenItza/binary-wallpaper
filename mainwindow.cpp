#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QPainter>
#include <exception>
#include <QDebug>

QString translateToBinary(QString original);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->previewBtn, &QPushButton::clicked, [this] {
        QString original_text = ui->textInput->toPlainText();
        int font_size = ui->fontSizeEdit->text().toInt();

        QPixmap previewPixmap(createPixmap(translateToBinary(original_text), font_size));
        ui->preview->setPixmap(previewPixmap.scaled(QSize(800,600)));
    });

    connect(ui->saveBtn, &QPushButton::clicked, [this] {
        QString original_text = ui->textInput->toPlainText();
        int font_size = ui->fontSizeEdit->text().toInt();

        saveImage(translateToBinary(original_text), font_size);
    });
}

QPixmap MainWindow::createPixmap(QString text, int font_size)
{
    QPixmap pixmap(1920, 1080);
    pixmap.fill(ui->bgColorEdit->text());

    QFont font(ui->fontComboBox->currentFont());
    font.setPixelSize(font_size);
    font.setBold((ui->boldBox->checkState() == Qt::Checked));
    font.setItalic((ui->italicBox->checkState() == Qt::Checked));
    font.setUnderline((ui->underlineBox->checkState() == Qt::Checked));

    QPainter p(&pixmap);
    p.setPen(QPen(ui->fgColorEdit->text()));
    p.setFont(font);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.drawText(pixmap.rect(), Qt::AlignCenter | Qt::TextWordWrap, text);

    return pixmap;
}

void MainWindow::saveImage(QString text, int font_size)
{
    QImage img(1920, 1080, QImage::Format_ARGB32);
    img.fill(ui->bgColorEdit->text());

    QFont font(ui->fontComboBox->currentFont());
    font.setPixelSize(font_size);
    font.setBold((ui->boldBox->checkState() == Qt::Checked));
    font.setItalic((ui->italicBox->checkState() == Qt::Checked));
    font.setUnderline((ui->underlineBox->checkState() == Qt::Checked));

    QPainter p(&img);
    p.setPen(QPen(ui->fgColorEdit->text()));
    p.setFont(font);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.drawText(img.rect(), Qt::AlignCenter | Qt::TextWordWrap, text);
    p.end();

    img.save("wallpaper.png", nullptr, 89);
}

QString translateToBinary(QString original)
{
    QByteArray original_array = original.toUtf8();

    QString translated;
    for (auto it = original_array.begin(); *it != '\0'; it++) {
        if (*it == '\n') {
            translated.push_back("\n ");
            continue;
        }

        QString temp;
        temp.push_back(QString::number((int)(*it), 2));

        //leading zeroes are omitted by QString::number, this fixes it
        while (temp.size() < 8)
            temp.push_front("0");

        temp.append(" ");

        translated.push_back(temp);
    }

    return translated;
}

MainWindow::~MainWindow()
{
    delete ui;
}
