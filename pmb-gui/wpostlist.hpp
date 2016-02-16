#ifndef WPOSTLIST_H
#define WPOSTLIST_H

#include <QWidget>
#include <QListView>
#include <blog/post.hpp>
#include <vector>

class WPostList : public QListView
{
    Q_OBJECT
public:
    explicit WPostList(QWidget *parent = 0);
    QString selected_post_id();

public slots:
    void set_post_list(std::vector<basics::Post>, int);
    void add_post(const basics::Post &post);
    void remove_post(const basics::Post &post);

signals:
    void selected_post_changed(const QString&);

private slots:
    void handle_indexes_moved(const QModelIndex& index);

private:
    QStringListModel *model_;
};

#endif // WPOSTLIST_H
