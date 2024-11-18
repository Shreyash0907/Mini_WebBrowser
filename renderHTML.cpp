#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTabBar>
#include <QPainter>
#include <QLabel>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QMessageBox>
#include <QTextEdit>
#include <QUrl>
#include <QDebug>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPixmap>
#include <QByteArray>
#include "node.hpp"
#include <QLineEdit>
#include <QScrollArea>
#include <QListWidget>


using namespace std;
// Custom Widget Class for Painting
class RenderTabWidget : public QWidget {

private:
     Node* root;
     int cnt = 0;
public:
    RenderTabWidget(Node* rootNode, QWidget *parent = nullptr)
        : QWidget(parent), root(rootNode) {
            // QLabel *label = new QLabel(this);
            // QLabel *label1 = new QLabel(this);
            this->setCursor(Qt::ArrowCursor);
            textEdit = new QTextEdit(this);
            textEdit->setReadOnly(true);
            textEdit->setFocusPolicy(Qt::NoFocus);
            textEdit->setCursor(Qt::ArrowCursor);
            textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
        // label->setText("This is a very\n long text...");
        // label1->setText("This is a very\n long text...");
        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &RenderTabWidget::onImageDownloaded);

        // // Create a layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QTextDocument *document = new QTextDocument(this);
        QTextCursor cursor(document);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);  // Make the content resize with the scroll area
        scrollArea->setWidget(textEdit); 
        

        QTextCharFormat charFormat;
        QFont font = charFormat.font();
        font.setPointSize(12); 
        font.setFamily("Times New Roman");
        charFormat.setFont(font);
        cursor.mergeCharFormat(charFormat);
        renderTags(root, cursor, charFormat);
        // Optionally, set layout margins to 0 to remove extra space
        layout->setContentsMargins(0, 0, 0, 0);
        // Add the label to the layout
        // layout->addWidget(label);
        // layout->addWidget(label1);
        textEdit->setDocument(document);
        layout->addWidget(scrollArea);
        // Set the layout for this widget
        setLayout(layout);
        }

    static string getTitle(Node* temp){
        if(temp == NULL){
            cout<<"null";
            return "";
        }
        cout<<temp->getType()<<" ";
        if(temp->getType() == 3){
            return string(*temp->getValue());
        }
        // cout<<temp->getType()<<" ";
        string title;
        for(auto i : temp->productions){
            title += getTitle(i);
            if(title != ""){
                break;
            }
        }
        return title;


    }
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        
    }
    void mousePressEvent(QMouseEvent *event) override {

        
        // Get the position of the mouse click relative to the widget
        QPoint pos = event->pos();

        // Use QTextEdit or any mechanism you have for rendering to get the cursor
        if (textEdit) {
            QTextCursor cursor = textEdit->cursorForPosition(pos);

            // Check if the clicked position has an anchor (link)
            if (cursor.charFormat().isAnchor()) {
                QString href = cursor.charFormat().anchorHref();
                qDebug() << "Anchor clicked:" << href;
                // Open the link using QDesktopServices
                QDesktopServices::openUrl(QUrl(href));
            }
        }

        // Call the base class implementation to handle other events
        QWidget::mousePressEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        // Set the cursor to ArrowCursor for any mouse move event
        this->setCursor(Qt::ArrowCursor);
        QWidget::mouseMoveEvent(event); 
    }

private slots:
    void onImageDownloaded(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            // Read the downloaded image data
            QByteArray imageData = reply->readAll();

            // Load the data into QImage
            image.loadFromData(imageData);

            // Trigger a repaint to display the image
            update();
        } else {
            qDebug() << "Failed to download image:" << reply->errorString();
        }

        // Clean up
        reply->deleteLater();
    }


private:

    QTextEdit *textEdit;
    QNetworkAccessManager *networkManager;
    QImage image;
    QUrl imageUrl;
    QString alt;
    
    void renderTags(Node* temp, QTextCursor &cursor, QTextCharFormat &charForm){
        if(temp == NULL){
            return;
        }
        QTextCharFormat savedCharFormat = cursor.charFormat();
        QTextBlockFormat savedBlockFormat = cursor.blockFormat();

        QTextCharFormat charFormat = cursor.charFormat();
        QTextBlockFormat blockFormat = cursor.blockFormat();
        cout<<temp->getType()<<" ";
        switch( temp->getType()){
            case Src:{
                QString url = QString::fromStdString(*temp->getValue());
                imageUrl = QUrl(url);
                break;
            }
            case Alt:{
                alt = QString::fromStdString(*temp->getValue());
                break;
            }
            case Image:{
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case ListElement:{
                for (auto i : temp->productions) {
                    renderTags(i, cursor, charFormat);
                    if(i->getType() == BodyContent){
                        QString qtitle = QString::fromStdString("\n");
                        cursor.insertText(qtitle);  // Render list item text
                    }
                    
                }
                
                break;
            }
            case OList: {  // Ordered List (OL)
                // Set up the font for list items
                QFont font = charFormat.font();
                font.setPointSize(12);  // Set the font size for list items
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                // Set up block format for indentation
                blockFormat.setTopMargin(4);
                blockFormat.setBottomMargin(4);
                blockFormat.setTextIndent(20);  // Indentation for list items
                cursor.setBlockFormat(blockFormat);

                // Set up the list format for ordered list (numbers)
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDecimal);  // Numbers for ordered list
                cursor.insertList(listFormat);  // Create the list in the document

                // Loop through the list items and render them
                for (auto i : temp->productions) {
                    renderTags(i, cursor, charFormat);  // Render list item text
                }
                break;
            }

            case UList: {  // Unordered List (UL)
                // Set up the font for list items
                QFont font = charFormat.font();
                font.setPointSize(12);  // Set the font size for list items
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                // Set up block format for indentation
                blockFormat.setTopMargin(4);
                blockFormat.setBottomMargin(4);
                blockFormat.setTextIndent(20);  // Indentation for list items
                cursor.setBlockFormat(blockFormat);

                // Set up the list format for unordered list (bullets)
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDisc);  // Bullets for unordered list
                cursor.insertList(listFormat);  // Create the list in the document

                // Loop through the list items and render them
                for (auto i : temp->productions) {
                    renderTags(i, cursor, charFormat);  // Render list item text
                }
                break;
            }
            case Anchor:{
                QFont font = charFormat.font();
                font.setUnderline(true);
                charFormat.setFont(font);
                charFormat.setForeground(Qt::blue);
                QString link = QString::fromStdString(*temp->getValue());
                charFormat.setAnchor(true);
                charFormat.setAnchorHref(link);
                cursor.mergeCharFormat(charFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case H1:{
                QFont font = charFormat.font();
                font.setPointSize(28);  
                font.setBold(true);   
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);
                blockFormat.setTopMargin(12);              
                blockFormat.setBottomMargin(16);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case H2:{
                QFont font = charFormat.font();
                font.setPointSize(24); 
                font.setBold(true);  
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);
 
                blockFormat.setTopMargin(12);              
                blockFormat.setBottomMargin(16);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case H3:{
                QFont font = charFormat.font();
                font.setPointSize(20); 
                font.setBold(true);  
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);
 
                blockFormat.setTopMargin(12);              
                blockFormat.setBottomMargin(12);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case H4:{
                QFont font = charFormat.font();
                font.setPointSize(16); 
                font.setBold(true);  
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);
 
                blockFormat.setTopMargin(12);              
                blockFormat.setBottomMargin(12);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case H5:{
                QFont font = charFormat.font();
                font.setPointSize(14); 
                font.setBold(true);  
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);
 
                blockFormat.setTopMargin(12);              
                blockFormat.setBottomMargin(12);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case Paragraph:{
                blockFormat.setBottomMargin(8);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case Strong:{
                QFont font = charFormat.font();
                font.setBold(true);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case Em:{
                QFont font = charFormat.font();
                font.setItalic(true);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case Blockquote:{
                QFont font = charFormat.font();
                font.setPointSize(11);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);
                blockFormat.setLeftMargin(40);  
                blockFormat.setRightMargin(40);  
                blockFormat.setTopMargin(12);      
                blockFormat.setBottomMargin(12); 
                // blockFormat.setAlignment(Qt::AlignLeft); 
                cursor.setBlockFormat(blockFormat);
                // blockFormat.setTopMargin(12);              
                // blockFormat.setBottomMargin(12);           
                // cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case Text:{
                paintText(temp, cursor, charFormat);
                break;
            }
            case TextContent:{
                paintText(temp, cursor, charFormat);
                break;
            }
            case Space:{
                paintText(temp, cursor, charFormat);
                break;
            }
            case Newline:{
                paintText(temp, cursor, charFormat);
                break;
            }
            case Pre:{
                QFont font = charFormat.font();
                font.setFamily("Courier New");  // Use a monospace font
                font.setPointSize(10);  // Set an appropriate font size for code or preformatted text
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                // Set block format to ensure proper line spacing
                blockFormat.setTopMargin(4);
                blockFormat.setBottomMargin(4);
                blockFormat.setTextIndent(0);  // No indentation
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            default:{
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
            }

        }


        
        
        
        // for(auto i : temp->productions){
        //     renderTags(i,cursor, charFormat);
        // }
        cursor.setCharFormat(savedCharFormat);  // Restore the original character format
        cursor.setBlockFormat(savedBlockFormat);
        
    }

    

    void renderListElements(Node *temp, QTextCursor &cursor){
        if(temp == NULL){
            return;
        }


    }

    void paintText(Node* temp, QTextCursor &cursor, QTextCharFormat &charFormat){
        if(temp == NULL){
            return;
        }
        
        QString qtitle = QString::fromStdString(*temp->getValue());
        cursor.insertText(qtitle);        
    }

    
};

// Main Window Class
class MainWindow : public QWidget {
public:
    MainWindow() {
        tabWidget = new QTabWidget(this);
        tabWidget->setWindowTitle("My Browser");

        tabWidget->setTabsClosable(true);

        connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

        QPushButton *addTabButton = new QPushButton("Search", this);
        addTabButton->setFixedWidth(150);
        addTabButton->setFixedHeight(40);
        QPushButton *historyTabButton = new QPushButton("History", this);
        historyTabButton->setFixedWidth(150);
        historyTabButton->setFixedHeight(40);
        connect(addTabButton, &QPushButton::clicked, this, &MainWindow::addTab);
        connect(historyTabButton, &QPushButton::clicked, this, &MainWindow::showHistory);

        // Create the QTextEdit section
        lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("Enter text here...");
        lineEdit->setFixedHeight(40); // Set the same width as the button
        QFont font = lineEdit->font();
        font.setPointSize(14); // Set the font size to 14 (adjust as needed)
        lineEdit->setFont(font);

        // Create a horizontal layout for the button and line edit
        QHBoxLayout *hLayout = new QHBoxLayout();
        hLayout->addWidget(lineEdit);
        hLayout->addWidget(addTabButton);
        hLayout->addWidget(historyTabButton);

        // Main vertical layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addLayout(hLayout); // Add the horizontal layout
        layout->addWidget(tabWidget);

        setLayout(layout);
        resize(1700, 1000);
    }

private slots:
    // Slot to add a new tab
    void addTab();

    // Slot to handle the tab close request
    void closeTab(int index) {
        // Check if the tab exists and confirm the close operation
        if (tabWidget->count() > 0) {
            tabWidget->removeTab(index);
        }
    }

    void showHistory(){
        QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);

    // Create a QListWidget to display the QString keys
    QListWidget *listWidget = new QListWidget(newTab);

    // Iterate through the tabMap and add the QString keys to the QListWidget
    for (const auto &pair : tabMap) {
        QListWidgetItem *item = new QListWidgetItem(pair.first);
    
        // Set the font size for this individual item
        QFont font = item->font();
        font.setPointSize(14); 
        // font.setBold(true);
        item->setFont(font);

        listWidget->addItem(item);
    }

    // Add the list widget to the layout
    layout->addWidget(listWidget);

    // Add the new tab to the QTabWidget
    tabWidget->addTab(newTab, "History");
    tabWidget->setCurrentWidget(newTab);
    }


    void refereshHistoryTab(){
        // int index = tabWidget->indexOf(tabWidget->findChild<QWidget*>("listWidget"));
        int index = -1;
        for (int i = 0; i < tabWidget->count(); ++i) {
            if (tabWidget->tabText(i) == "History") {
                index = i;  // Return the index of the tab whose title matches
            }
        }

        if(index != -1){
            // if (tabMap == nullptr) return; // Check if listWidget has been created

            QWidget *newTab = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(newTab);

            // Create a QListWidget to display the QString keys
            QListWidget *listWidget = new QListWidget(newTab);
            

            // Iterate through the tabMap and add the QString keys to the QListWidget
            for (const auto &pair : tabMap) {
                
                QListWidgetItem *item = new QListWidgetItem(pair.first);
    
                // Set the font size for this individual item
                QFont font = item->font();
                font.setPointSize(14); 
                // font.setBold(true);
                item->setFont(font);

                listWidget->addItem(item);
            }

            // Add the list widget to the layout
            layout->addWidget(listWidget);

            tabWidget->removeTab(index);  // Remove the old tab at index 1
            tabWidget->insertTab(index, newTab, "History");  // Insert the new tab at index 1
            }
        cout<<index<<" index of History"<<std::endl;

    }

private:
    QTabWidget *tabWidget;
    QLineEdit *lineEdit;
    std::map<QString, RenderTabWidget*> tabMap;
    // QProcess *process;
};

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     MainWindow window;
//     window.show();

//     return app.exec();
// }
