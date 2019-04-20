#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QFile>
#include <QTextStream>

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

    void load (QString filename, const std::vector<Material> &materials=std::vector<Material>());

private:
    Scene *m_scene;
};

#endif // MAINWINDOW_HPP
