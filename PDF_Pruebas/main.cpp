#include <QApplication>
#include <QPainter>
#include <QPdfWriter>
#include <QImage>

void generatePdf(const QString& filePath, const QString& text, const QString& imagePath)
{
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::Letter));
    pdfWriter.setPageMargins(QMarginsF(30, 15, 30, 30));

    QPainter painter(&pdfWriter);
    painter.setFont(QFont("Times New Roman", 12));

    qDebug() << "WIDTH: " << pdfWriter.width();

    // Load the image
    QImage image(imagePath);
    if (!image.isNull()) {

        qDebug() << "Image dimensions: " << image.width() << "x" << image.height();

        // Scale the image to fit within the page width
        QImage scaledImage = image.scaledToWidth(pdfWriter.width() - 5000, Qt::SmoothTransformation);

        // Calculate the position to draw the image
        QRectF imageRect(pdfWriter.width() - 1500, pdfWriter.height() - 12000, scaledImage.width(), scaledImage.height());

        // Draw the image
        painter.drawImage(imageRect, scaledImage);
    } else {
        qDebug() << "Failed to load image: " << imagePath;
    }

    // Draw the text
    painter.drawText(QRectF(15, 15, pdfWriter.width() - 60, pdfWriter.height() - 190), text);

    painter.end();

    qDebug() << "Left the function ";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString filePath = "output.pdf";
    QString imagePath = "pollitos_incorporated_icon.png";

    generatePdf(filePath, "Hello, World!", imagePath);

    return app.exec();
}
