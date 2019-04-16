#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QString>

#include "renderer/Scene.hpp"
#include "renderer/objects/Sphere.hpp"
#include "renderer/objects/Triangle.hpp"
#include "renderer/objects/Group.hpp"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void load (QString filename);

private:
    Scene *m_scene;
};

#endif // MAINWINDOW_HPP
