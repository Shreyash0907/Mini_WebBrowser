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
#include <QSettings>
#include <bits/stdc++.h>

using namespace std;

using Time = std::chrono::system_clock::time_point; 

class MainWindow : public QWidget {
public:
    QTabWidget *tabWidget;
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
        


        lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("Enter text here...");
        lineEdit->setFixedHeight(40); // Set the same width as the button
        QFont font = lineEdit->font();
        font.setPointSize(14);
        lineEdit->setFont(font);

        listWidget = new QListWidget(new QWidget());

        connect(listWidget, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);
        

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

    ~MainWindow(){
        QSettings settings("MyCompany", "MyApp");
        settings.clear();
        int cnt = tabWidget->count();
        for(int i = 0 ; i < cnt; i++){
            string str = tabWidget->tabText(i).toStdString();
            string url = urlMap[str];
            settings.setValue(QString::fromStdString(url), 1);
        }
    }

    void renderHistory(string URL);

    void renderAnchor(string URL);

    void loadData(){
        QSettings settings("MyCompany", "MyApp");
        QStringList keys = settings.allKeys();
    
        for (const QString &key : keys) {
            QVariant value = settings.value(key);
            string url = key.toStdString();
            cout<<"setting url "<<url<<" "<<std::flush;
            renderHistory(url);
        }
    }

    void goBack(){
    //     int curr = tabWidget->currentIndex();
    //     string title = tabWidget->tabText(curr).toStdString();

    //     if(!undo.empty()){
    //         tabWidget->removeTab(curr);
    //         // tabWidget->insertTab(curr, undo.top(), title);
    //     }
    }

    void goForward(){
    //     int curr = tabWidget->currentIndex();
    //     string title = tabWidget->tabText(curr).toStdString();

    }
    

private slots:
    // Slot to add a new tab
    void addTab();

    void onItemClicked(QListWidgetItem *item){

        cout<<"clicked "<<std::flush;
        QString itemText = item->text();

        string temp;
        for(auto i: tabMap){
            if(i.first == itemText){
                temp = i.second.first;
                cout<<"found";
            }
        }
        cout<<temp<<"  url";
        renderHistory(temp);

    }

    void closeTab(int index) {

        if (tabWidget->count() > 0) {
            tabWidget->removeTab(index);
        }
    }

    void showHistory(){
        QWidget *newTab = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(newTab);


        for (auto it = tabMap.rbegin(); it != tabMap.rend(); ++it) {

            const auto &pair = *it;
            QListWidgetItem *item = new QListWidgetItem(pair.first);
        
            QFont font = item->font();
            font.setPointSize(14); 

            item->setFont(font);

            listWidget->addItem(item);
        }

        layout->addWidget(listWidget);

        tabWidget->addTab(newTab, "History");
        tabWidget->setCurrentWidget(newTab);
        
    }


    void refereshHistoryTab(){

        int index = -1;
        for (int i = 0; i < tabWidget->count(); ++i) {
            if (tabWidget->tabText(i) == "History") {
                index = i;  
            }
        }

        if(index != -1){


            QWidget *newTab = new QWidget();
            QVBoxLayout *layout = new QVBoxLayout(newTab);

            
            listWidget->clear();


            for (auto it = tabMap.rbegin(); it != tabMap.rend(); ++it) {
               
                const auto &pair = *it;
                auto epoch = std::chrono::system_clock::to_time_t(pair.second.second);
                QDateTime dateTime = QDateTime::fromSecsSinceEpoch(epoch);

                QString timeString = dateTime.toString("yyyy-MM-dd HH:mm:ss");

                int le = pair.first.length();

                QString space = " ";
                QString title = pair.first;
                
                for(int i = le; i <= 60; i++){
                    title.append(space);
                }
                            
                QListWidgetItem *item = new QListWidgetItem(pair.first);
 
                QFont font = item->font();
                font.setPointSize(14); 

                item->setFont(font);

                listWidget->addItem(item);
                string url = pair.second.first;
                

            }

            layout->addWidget(listWidget);

            tabWidget->removeTab(index); 
            tabWidget->insertTab(index, newTab, "History"); 
            }
        cout<<index<<" index of History"<<std::endl;

    }

private:
    
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    std::vector<std::pair<QString, pair<string,Time>>> tabMap;
    unordered_map<string,  string> urlMap;
    // stack<QWidget*> undo, redo;

};


class RenderTabWidget : public QWidget {

private:
     Node* root;
     int cnt = 0;
     MainWindow* mainWindow;
public:
    RenderTabWidget(Node* rootNode,MainWindow* parentWindow, QWidget *parent = nullptr)
        : QWidget(parent), root(rootNode),mainWindow(parentWindow) {

            this->setCursor(Qt::ArrowCursor);
            textEdit = new QTextEdit(this);
            textEdit->setReadOnly(true);
            textEdit->setFocusPolicy(Qt::NoFocus);
            textEdit->setCursor(Qt::ArrowCursor);
            textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &RenderTabWidget::onImageDownloaded);

        // // Create a layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QTextDocument *document = new QTextDocument(this);
        QTextCursor cursor(document);

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true); 
        scrollArea->setWidget(textEdit); 
        

        QTextCharFormat charFormat;
        QFont font = charFormat.font();
        font.setPointSize(12); 
        font.setFamily("Times New Roman");
        charFormat.setFont(font);
        cursor.mergeCharFormat(charFormat);
        renderTags(root, cursor);

        layout->setContentsMargins(0, 0, 0, 0);

        textEdit->setDocument(document);
        layout->addWidget(scrollArea);
        QPushButton *undoButton = new QPushButton("Undo", this);
        QPushButton *redoButton = new QPushButton("Redo", this);

        connect(redoButton, &QPushButton::clicked, this, &RenderTabWidget::goForward);
        connect(undoButton, &QPushButton::clicked, this, &RenderTabWidget::goBack);


        // Create a horizontal layout for the buttons
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(undoButton);
        buttonLayout->addWidget(redoButton);

        // Add the button layout to the main vertical layout
        layout->addLayout(buttonLayout);

        setLayout(layout);
        }

    stack<pair<RenderTabWidget*,string> > undo,redo;

    void goForward(){
        if(!redo.empty()){
            // undo.push(redo.top());
            RenderTabWidget* current = redo.top().first;
            int curr = mainWindow->tabWidget->currentIndex();
            string retrieveTitle = mainWindow->tabWidget->tabText(curr).toStdString();
            RenderTabWidget* retrievedTab = static_cast<RenderTabWidget*>(mainWindow->tabWidget->widget(curr));
            current->undo.push(make_pair(retrievedTab, retrieveTitle));
            mainWindow->tabWidget->removeTab(curr);
            string title = redo.top().second;
            mainWindow->tabWidget->insertTab(curr, current, QString::fromStdString(title));
            redo.pop();
            cout<<title<<" redo title "<<endl;
            cout<<retrieveTitle<<"  title "<<endl;
        }
        else{
            int curr = mainWindow->tabWidget->currentIndex();
            string retrieveTitle = mainWindow->tabWidget->tabText(curr).toStdString();
            cout<<retrieveTitle<<"redo empty"<<endl;
        }
    }

    void goBack(){
        if(!undo.empty()){
            RenderTabWidget* current = undo.top().first;
            
            int curr = mainWindow->tabWidget->currentIndex();
            string retrieveTitle = mainWindow->tabWidget->tabText(curr).toStdString();
            RenderTabWidget* retrievedTab = static_cast<RenderTabWidget*>(mainWindow->tabWidget->widget(curr));
            current->redo.push(make_pair(retrievedTab, retrieveTitle));
            mainWindow->tabWidget->removeTab(curr);
            string title = undo.top().second;
            mainWindow->tabWidget->insertTab(curr, current, QString::fromStdString(title));
            undo.pop();
            cout<<title<<" undo title "<<endl;
            cout<<retrieveTitle<<" current titel"<<endl;
        }
        else{
            int curr = mainWindow->tabWidget->currentIndex();
            string retrieveTitle = mainWindow->tabWidget->tabText(curr).toStdString();
            cout<<retrieveTitle<<"undo empty"<<endl;
        }
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
    
    void mousePressEvent(QMouseEvent *event) override {

        QPoint pos = event->pos();

        if (textEdit) {
            QTextCursor cursor = textEdit->cursorForPosition(pos);

            if (cursor.charFormat().isAnchor()) {
                QString href = cursor.charFormat().anchorHref();
                qDebug() << "Anchor clicked:" << href;
                
                mainWindow->renderAnchor(href.toStdString());
            }
        }

        QWidget::mousePressEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {

        this->setCursor(Qt::ArrowCursor);
        QWidget::mouseMoveEvent(event); 
    }

    void renderImage(){
        QNetworkRequest request(imageUrl);
        networkManager->get(request);

    }

private slots:
    void onImageDownloaded(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();

            QPixmap pixmap;

            pixmap.loadFromData(imageData);
            if(pixmap.isNull()){
                cout<<"image null"<<std::flush;
                return ;
            }else{
                cout<<"image loaded "<<std::flush;
            }
            image = pixmap.toImage();
            if(image.isNull()){
                cout<<"image null"<<std::flush;
            }else{
                cout<<"image not null"<<std::flush;
            }
            
            imageFormat.setName(reply->url().toString()); 
            imageFormat.setWidth(200); 
            imageFormat.setHeight(200);


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
    QTextImageFormat imageFormat;

   
    
    void renderTags(Node* temp, QTextCursor &cursor){
        if(temp == NULL){
            return;
        }
        QTextCharFormat savedCharFormat = cursor.charFormat();
        QTextBlockFormat savedBlockFormat = cursor.blockFormat();

        QTextCharFormat charFormat = cursor.charFormat();
        QTextBlockFormat blockFormat = cursor.blockFormat();
        switch( temp->getType()){
            case Src:{
                QString url = QString::fromStdString(*temp->getValue());
                imageUrl = QUrl(url);
                renderImage();

                cursor.insertImage(imageFormat);
                cursor.insertImage(image);
                break;
            }
            case Alt:{
                alt = QString::fromStdString(*temp->getValue());
                break;
            }
            case Image:{
                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
                
                break;
            }
            case ListElement:{
                for (auto i : temp->productions) {
                    renderTags(i, cursor);
                    if(i->getType() == BodyContent){
                        QString qtitle = QString::fromStdString("\n");
                        cursor.insertText(qtitle); 
                    }
                    
                }
                
                break;
            }
            case OList: {  
                QFont font = charFormat.font();
                font.setPointSize(12);  
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                blockFormat.setTopMargin(4);
                blockFormat.setBottomMargin(4);
                blockFormat.setTextIndent(20);  
                cursor.setBlockFormat(blockFormat);

                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDecimal); 
                cursor.insertList(listFormat);  
                for (auto i : temp->productions) {
                    renderTags(i, cursor);
                }
                break;
            }

            case UList: { 
                QFont font = charFormat.font();
                font.setPointSize(12); 
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                blockFormat.setTopMargin(4);
                blockFormat.setBottomMargin(4);
                blockFormat.setTextIndent(20);  
                cursor.setBlockFormat(blockFormat);

               
                QTextListFormat listFormat;
                listFormat.setStyle(QTextListFormat::ListDisc);  // Bullets for unordered list
                cursor.insertList(listFormat);  // Create the list in the document

                // Loop through the list items and render them
                for (auto i : temp->productions) {
                    renderTags(i, cursor);  // Render list item text
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
                    renderTags(i, cursor);
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
                    renderTags(i, cursor);
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
                    renderTags(i, cursor);
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
                    renderTags(i, cursor);
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
                    renderTags(i, cursor);
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
                    renderTags(i, cursor);
                }
                break;
            }
            case Paragraph:{
                blockFormat.setBottomMargin(8);           
                cursor.setBlockFormat(blockFormat);
                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
                break;
            }
            case Strong:{
                QFont font = charFormat.font();
                font.setBold(true);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
                break;
            }
            case Em:{
                QFont font = charFormat.font();
                font.setItalic(true);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
                break;
            }
            case Underline:{
                QFont font = charFormat.font();
                font.setUnderline(true);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
                break;
            }
            case Small:{
                QFont font = charFormat.font();
                font.setPointSize(10);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
                break;
            }
            case Code:{
                QFont font = charFormat.font();
                font.setFamily("Courier New");  // Use a monospace font
                font.setPointSize(10);
                charFormat.setFont(font);
                cursor.mergeCharFormat(charFormat);

                for(auto i : temp->productions){
                    renderTags(i, cursor);
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
                    renderTags(i, cursor);
                }
                break;
            }
            case Text:{
                paintText(temp, cursor);
                break;
            }
            case TextContent:{
                paintText(temp, cursor);
                break;
            }
            case Space:{
                paintText(temp, cursor);
                break;
            }
            case Newline:{
                paintText(temp, cursor);
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
                    renderTags(i, cursor);
                }
                break;
            }
            default:{
                for(auto i : temp->productions){
                    renderTags(i, cursor);
                }
            }

        }


        
        
        
        
        cursor.setCharFormat(savedCharFormat);  // Restore the original character format
        cursor.setBlockFormat(savedBlockFormat);
        
    }

    

    

    void paintText(Node* temp, QTextCursor &cursor){
        if(temp == NULL){
            return;
        }
        
        QString qtitle = QString::fromStdString(*temp->getValue());
        cursor.insertText(qtitle);        
    }

    
};

