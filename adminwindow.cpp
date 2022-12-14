#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "share.h"

adminwindow::adminwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminwindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QStringLiteral("房屋出租信息管理系统-管理员端"));

    connect(ui->quitButton,&QPushButton::clicked ,[this](){
        this->close();
    }); //用信号实现退出

    //更新数据
    QSqlQuery query,query1;
    query.prepare("select house_id from house where timestampdiff(day,renting_end,now())>0");
    if(query.exec()){
       while (query.next()){
               query1.exec(QString("update house set house_tenant = null ,renting_end =null where house_id = %1").arg(query.value(0).toInt()));
        }

    }
    //初始化
    model_t = new QSqlTableModel(this);
    model_l = new QSqlTableModel(this);
    model_h = new QSqlTableModel(this);
    model_r = new QSqlTableModel(this);
    model_ta = new QSqlTableModel(this);
    model_la = new QSqlTableModel(this);


    model_t ->setTable("tenant");
    model_t->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置手动更改
    model_t->select();

    model_l ->setTable("landlord");
    model_l->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_l->select();

    model_h ->setTable("house");
    model_h->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_h->select();

    model_r ->setTable("record");
    model_r->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_r->select();

    model_ta ->setTable("tenant_account");
    model_ta->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_ta->select();

    model_la ->setTable("landlord_account");
    model_la->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_la->select();

    //视图绑定
    ui->a_tenantview->setModel(model_t);
    ui->a_landlordview->setModel(model_l);
    ui->a_houseview->setModel(model_h);
    ui->a_recordview->setModel(model_r);
    ui->a_tacview->setModel(model_ta);
    ui->a_lacview->setModel(model_la);

    ui->a_tenantview->verticalHeader()->hide();  //隐藏左侧索引
    ui->a_tenantview->resizeColumnsToContents();   //自适应调整
    ui->a_tenantview->setAlternatingRowColors(true);  //行之间颜色变化
    ui->a_tenantview->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止更改


    ui->a_landlordview->verticalHeader()->hide();
    ui->a_landlordview->resizeColumnsToContents();
    ui->a_landlordview->setAlternatingRowColors(true);
    ui->a_landlordview->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止更改

    ui->a_houseview->verticalHeader()->hide();
    ui->a_houseview->resizeColumnsToContents();
    ui->a_houseview->setAlternatingRowColors(true);
    ui->a_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止更改


    ui->a_recordview->verticalHeader()->hide();
    ui->a_recordview->resizeColumnsToContents();
    ui->a_recordview->setAlternatingRowColors(true);
    ui->a_recordview->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止更改



    ui->a_tacview->verticalHeader()->hide();
    ui->a_tacview->resizeColumnsToContents();
    ui->a_tacview->setAlternatingRowColors(true);
    ui->a_tacview->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止更改

    ui->a_lacview->verticalHeader()->hide();
    ui->a_lacview->resizeColumnsToContents();
    ui->a_lacview->setAlternatingRowColors(true);
    ui->a_lacview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置取消和提交按键初始不可用
    ui->cancelButton->setDisabled(true);
    ui->commitButton->setDisabled(true);

}

adminwindow::~adminwindow()
{
    delete ui;
}







void adminwindow::on_addButton_clicked() //新增
{
    int index = ui->tabWidget->currentIndex();
    if(index>3){
        QMessageBox::warning(NULL,"操作取消","你没有权限更改");
        return;
    }
    ui->addButton->setDisabled(true);
    ui->updateButton->setDisabled(true);
    ui->delButton->setDisabled(true);
    ui->cancelButton->setEnabled(true);
    ui->commitButton->setEnabled(true);
    ui->pushButton_2->setDisabled(true);

    int rowCount; //rowcount变量定义在switch外    C++不允许跨过变量的初始化语句直接跳转到该变量作用域的另一个位置。

    switch(index){

        case(0):
                //设置禁用其他标签页面

                ui->tabWidget->setTabEnabled(1,false);
                ui->tabWidget->setTabEnabled(2,false);
                ui->tabWidget->setTabEnabled(3,false);
                ui->tabWidget->setTabEnabled(4,false);
                ui->tabWidget->setTabEnabled(5,false);

                while (model_t->canFetchMore()) {
                    model_t->fetchMore();
                }
                rowCount = model_t->rowCount();

                model_t->insertRow(rowCount);
                model_t->setData(model_t->index(rowCount, 0), ""); //添加行
                ui->a_tenantview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
                ui->a_tenantview->scrollToBottom(); //滚动到底部
                break;

        case(1):
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(2,false);
            ui->tabWidget->setTabEnabled(3,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
             while (model_l->canFetchMore()) {
                    model_l->fetchMore();
                }
                rowCount = model_l->rowCount();

                model_l->insertRow(rowCount);
                model_l->setData(model_l->index(rowCount, 0), ""); //添加行
             ui->a_landlordview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
             ui->a_landlordview->scrollToBottom(); //滚动到底部
        break;
        case(2):
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(3,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
             while (model_h->canFetchMore()) {
                    model_h->fetchMore();
                }
                rowCount = model_h->rowCount();

                model_h->insertRow(rowCount);
                model_h->setData(model_h->index(rowCount, 0), ""); //添加行
             ui->a_houseview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
             ui->a_houseview->scrollToBottom(); //滚动到底部


        break;
        case(3):
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
             while (model_r->canFetchMore()) {
                    model_r->fetchMore();
                }
                rowCount = model_r->rowCount();

                model_r->insertRow(rowCount);
                model_r->setData(model_r->index(rowCount, 0), ""); //添加行
             ui->a_recordview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
             ui->a_recordview->scrollToBottom(); //滚动到底部
        break;
    }
}


void adminwindow::on_cancelButton_clicked()     //取消
{
    int index = ui->tabWidget->currentIndex();

    ui->addButton->setEnabled(true);
    ui->updateButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->delButton->setEnabled(true);
    ui->cancelButton->setDisabled(true);
    ui->commitButton->setDisabled(true);


    ui->tabWidget->setTabEnabled(0,true);
    ui->tabWidget->setTabEnabled(1,true);
    ui->tabWidget->setTabEnabled(2,true);
    ui->tabWidget->setTabEnabled(3,true);
    ui->tabWidget->setTabEnabled(4,true);
    ui->tabWidget->setTabEnabled(5,true);
    switch(index){
        case(0):
            model_t->revertAll();
            ui->a_tenantview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_landlordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
             ui->a_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_recordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
        break;
        case(1):
            model_l->revertAll();
            ui->a_tenantview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_landlordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
             ui->a_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_recordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
        break;
        case(2):
            model_h->revertAll();
            ui->a_tenantview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_landlordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
             ui->a_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_recordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
        break;
        case(3):
            model_r->revertAll();
            ui->a_tenantview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_landlordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
             ui->a_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->a_recordview->setEditTriggers(QAbstractItemView::NoEditTriggers);
        break;
    }



}


void adminwindow::on_updateButton_clicked()     //更改
{
    int index = ui->tabWidget->currentIndex();
    if(index>3){
        QMessageBox::warning(NULL,"操作取消","你没有权限更改");
        return;
    }


    ui->addButton->setDisabled(true);
    ui->updateButton->setDisabled(true);
    ui->delButton->setDisabled(true);
    ui->cancelButton->setEnabled(true);
    ui->commitButton->setEnabled(true);
    ui->pushButton_2->setDisabled(true);

    switch(index){
        case(0):
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);
            ui->tabWidget->setTabEnabled(3,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
            ui->a_tenantview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
        break;
        case(1):
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(2,false);
            ui->tabWidget->setTabEnabled(3,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
            ui->a_landlordview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
        break;
        case(2):
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(3,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
            ui->a_houseview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
        break;
        case(3):
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);
            ui->tabWidget->setTabEnabled(4,false);
            ui->tabWidget->setTabEnabled(5,false);
            ui->a_recordview->setEditTriggers(QTableView::DoubleClicked); //双击编辑
        break;
    }
}


void adminwindow::on_delButton_clicked()        //删除
{
    int index = ui->tabWidget->currentIndex();
    if(index>3){
        QMessageBox::warning(NULL,"操作取消","你没有权限更改");
        return;
    }
    QModelIndex i ;
    int check;
    switch(index){
        case(0):
        i = ui->a_tenantview->currentIndex();//获取当前行
        model_t->removeRow(i.row());       //删除当前行
        check= QMessageBox::warning(this, "你正在删除当前行", "是否删除当前行？", QMessageBox::Yes, QMessageBox::No);  // 弹框确认
           if (check == QMessageBox::No) {
               model_t->revertAll();
               return;
           }
           model_t->submitAll();
           model_t->select();
        break;
        case(1):
            i = ui->a_landlordview->currentIndex();//获取当前行
            model_l->removeRow(i.row());       //删除当前行
            check= QMessageBox::warning(this, "你正在删除当前行", "是否删除当前行？", QMessageBox::Yes, QMessageBox::No);  // 弹框确认
               if (check == QMessageBox::No) {
                   model_l->revertAll();
                   return;
               }
               model_l->submitAll();
               model_l->select();
        break;
        case(2):
            i = ui->a_houseview->currentIndex();//获取当前行
            model_h->removeRow(i.row());       //删除当前行
            check= QMessageBox::warning(this, "你正在删除当前行", "是否删除当前行？", QMessageBox::Yes, QMessageBox::No);  // 弹框确认
               if (check == QMessageBox::No) {
                   model_h->revertAll();
                   return;
               }
               model_h->submitAll();
               model_h->select();
        break;
        case(3):
            i = ui->a_recordview->currentIndex();//获取当前行
            model_r->removeRow(i.row());       //删除当前行
            check= QMessageBox::warning(this, "你正在删除当前行", "是否删除当前行？", QMessageBox::Yes, QMessageBox::No);  // 弹框确认
               if (check == QMessageBox::No) {
                   model_r->revertAll();
                   return;
               }
               model_r->submitAll();
               model_r->select();
        break;
    }

}


void adminwindow::on_commitButton_clicked() //提交
{

    int index = ui->tabWidget->currentIndex();

    int check;

    switch(index){
        case(0):
            check= QMessageBox::warning(this, "你可能对该表进行了修改", "是否提交修改？", QMessageBox::Yes, QMessageBox::No);
            if (check == QMessageBox::No) {

                return;
         }
            model_t->submitAll();     //提交修改
            model_t->select();
            ui->a_tenantview->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置为禁止修改
        break;
        case(1):
            check= QMessageBox::warning(this, "你可能对该表进行了修改", "是否提交修改？", QMessageBox::Yes, QMessageBox::No);
            if (check == QMessageBox::No) {

                return;
            }
            model_l->submitAll();     //提交修改
            model_l->select();
            ui->a_landlordview->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置为禁止修改
        break;
        case(2):
            check= QMessageBox::warning(this, "你可能对该表进行了修改", "是否提交修改？", QMessageBox::Yes, QMessageBox::No);
            if (check == QMessageBox::No) {

                return;
            }
            model_h->submitAll();     //提交修改
            model_h->select();
            ui->a_houseview->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置为禁止修改
        break;
        case(3):
            check= QMessageBox::warning(this, "你可能对该表进行了修改", "是否提交修改？", QMessageBox::Yes, QMessageBox::No);
            if (check == QMessageBox::No) {

                return;
            }
            model_r->submitAll();     //提交修改
            model_r->select();
            ui->a_recordview->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置为禁止修改
        break;


    }
    //更改回初始化后状态

    ui->addButton->setEnabled(true);
    ui->updateButton->setEnabled(true);
    ui->delButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->cancelButton->setDisabled(true);
    ui->commitButton->setDisabled(true);

    ui->tabWidget->setTabEnabled(0,true);
    ui->tabWidget->setTabEnabled(1,true);
    ui->tabWidget->setTabEnabled(2,true);
    ui->tabWidget->setTabEnabled(3,true);
    ui->tabWidget->setTabEnabled(4,true);
    ui->tabWidget->setTabEnabled(5,true);




}



void adminwindow::on_pushButton_2_clicked() //刷新
{
    int index = ui->tabWidget->currentIndex();
    switch(index){
        case(0):
            model_t ->setTable("tenant");
            model_t->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置手动更改
            model_t->select();
        break;
        case(1):
            model_l ->setTable("landlord");
            model_l->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model_l->select();
        break;
        case(2):
            model_h ->setTable("house");
            model_h->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model_h->select();
        break;
        case(3):
            model_r ->setTable("record");
            model_r->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model_r->select();
        break;
        case(4):
            model_ta ->setTable("tenant_account");
            model_ta->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model_ta->select();
        break;
        case(5):       
            model_la ->setTable("landlord_account");
            model_la->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model_la->select();
        break;
    }
}



void adminwindow::on_a_rentingrecordButton_clicked() //正在生效的交易记录
{
    model_r->setTable("renting_record");
    model_r->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置手动更改
    model_r->select();
}


void adminwindow::on_a_house_countButton_clicked() //房屋数量
{
    model_h->setTable("count_house");
    model_h->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_h->select();
    ui->a_houseview->resizeColumnsToContents();

}


void adminwindow::on_a_landlord_countButton_clicked() //房东数量
{
    model_l->setTable("count_landlord");
    model_l->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_l->select();
    ui->a_landlordview->resizeColumnsToContents();
}



void adminwindow::on_a_l_hButton_clicked()          //房东-房屋一览
{
    model_l->setTable("landlord_house");
    model_l->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_l->select();
    ui->a_landlordview->resizeColumnsToContents();

}





void adminwindow::on_a_tenant_countButton_clicked() //租客数量
{
    model_t->setTable("count_tenant");
    model_t->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_t->select();
    ui->a_tenantview->resizeColumnsToContents();

}

