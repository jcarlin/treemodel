# treemodel
===========
Qt's simpletreemodel example, expanded to also display sql data in QTableView, QTreeView as well as QML TableView and TreeView.

#### This test app does _not_ include:
- login (hardcoded login params required in main.cpp)
- further nested classes
- multiple TreeModels
- interface class for ui to call, this class could also handle the proper assembly of the tree model and items 

#### Other features or benefits of a tree model might include: 
- lazy loading, eager loading and asynchornous querying and assembly of data

#### Imporant notes:
- In my testing, QML TreeView only worked with Qt 5.7, I have no idea why and there were some hints of Qt bugs around this. I moved on as soon as it worked. TLDR; Requires Qt 5.7.
