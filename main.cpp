#include <QApplication>
#include "renderHTML.cpp"  // Include the file that contains the MainWindow definition
#include "parser.cpp"
// #include "lex.cpp"
#include <fstream>


/// @brief Function used to create the token from input file. 
extern int yylex(void);

/// @brief Function used to parse the input token and creates the AST.
extern int yyparse(void);

/// @brief Function returns the root Node of the AST after the completion of parsing.
/// @return Object of Node.
extern Node* getRoot();

Node* Root;

void MainWindow::addTab() {
        Node* temp = Root;
        RenderTabWidget* newTab = new RenderTabWidget(Root);
        string title = RenderTabWidget::getTitle(temp);
        QString qtitle = QString::fromStdString(title);
        tabWidget->addTab( newTab, qtitle); // Add a new tab with the next index
    }

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const char* inputFile = "html_page_1.html";
    FILE *inputPtr;
    inputPtr = fopen(inputFile, "r");
    extern FILE *yyin;
    yyin = inputPtr;
    yyparse();
    Root = getRoot();
    
    MainWindow window;
    window.show();

    return app.exec();
}
