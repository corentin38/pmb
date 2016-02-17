#include "wpostlist.hpp"
#include <iostream>
#include <QStringListModel>

WPostList::WPostList(QWidget *parent) : QListView(parent), model_(new QStringListModel())
{
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setModel(model_);

    connect(this, SIGNAL (clicked(const QModelIndex&)),
            this, SLOT (handle_indexes_moved(const QModelIndex&)));
}

QString WPostList::selected_post_id()
{
    return this->currentIndex().data().toString();
}

void WPostList::set_post_list(std::vector<basics::Post> posts)
{
    std::vector<basics::Post>::const_iterator it = posts.begin();
    std::vector<basics::Post>::const_iterator end = posts.end();

    QStringList post_id_list;

    for (; it != end; ++it) {
        post_id_list << QString::fromStdString(it->get_timestamp_str());
    }

    model_->setStringList(post_id_list);
    this->setModel(model_);

    if (posts.size() > 0) {
        QModelIndex index = model_->index(0);
        this->setCurrentIndex(index);
        emit selected_post_changed(index.data().toString());
    } else {
        emit empty();
    }
}

void WPostList::add_post(const basics::Post& post)
{
    QString line = QString::fromStdString(post.get_timestamp_str());

    QStringList actual = model_->stringList();
    if (actual.indexOf(line) < 0) {
        actual.insert(0, line);
    }

    model_->setStringList(actual);
    this->setModel(model_);
    this->setCurrentIndex(model_->index(0));
    emit selected_post_changed(line);
}

void WPostList::remove_post(const QString& post_id)
{
    QStringList actual = model_->stringList();
    int index = actual.indexOf(post_id);
    if (index >= 0) {
        actual.removeAt(index);
    }

    model_->setStringList(actual);
    this->setModel(model_);
    if (actual.size() > 0) {
        int next = 0;
        if (index > 0) next = index - 1;
        QModelIndex index2 = model_->index(next);
        this->setCurrentIndex(index2);
        emit selected_post_changed(index2.data().toString());
    } else {
        emit empty();
    }
}

void WPostList::handle_indexes_moved(const QModelIndex &index)
{
    QString post_id = index.data().toString();
    emit selected_post_changed(post_id);
}
