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
#include "node.hpp"

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

        // // Create a layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QTextDocument *document = new QTextDocument(this);
        QTextCursor cursor(document);
        

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
        layout->addWidget(textEdit);
        // Set the layout for this widget
        setLayout(layout);
        }

    static string getTitle(Node* temp){
        if(temp == NULL){
            return "";
        }

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

private:

    QTextEdit *textEdit;
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
            case A:{
                QFont font = charFormat.font();
                font.setUnderline(true);
                charFormat.setFont(font);
                charFormat.setForeground(Qt::blue);
                QString link = QString::fromStdString(*temp->getValue());
                cout<<*temp->getValue();
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
                for(auto i : temp->productions){
                    renderTags(i, cursor, charFormat);
                }
                break;
            }
            case OList:{
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDisc);

                for(auto node: temp->productions){
                    renderListElements(node, cursor);
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

        // tabWidget->addTab(new RenderTabWidget(), "Tab 1");

        // tabWidget->addTab(new QWidget(), "Tab 2");

        tabWidget->setTabsClosable(true);

        connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

        QPushButton *addTabButton = new QPushButton("Add Tab", this);
        connect(addTabButton, &QPushButton::clicked, this, &MainWindow::addTab);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(tabWidget);
        layout->addWidget(addTabButton);
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

private:
    QTabWidget *tabWidget;
};

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     MainWindow window;
//     window.show();

//     return app.exec();
// }
