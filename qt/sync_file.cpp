#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>

bool sync(const QString& src, const QString& dst)
{
    QDir src_dir(src);
    QDir dst_dir(dst);

    if (!src_dir.exists()) {
        qInfo() << "src path not exists";
        return false;
    }

    QFileInfoList src_file(
        src_dir.entryInfoList(QDir::Filter::Files | QDir::Filter::Dirs
                              | QDir::Filter::NoDotAndDotDot));

    QFileInfoList dst_file(
        dst_dir.entryInfoList(QDir::Filter::Files | QDir::Filter::Dirs
                              | QDir::Filter::NoDotAndDotDot));

    for (auto& i : src_file) {
        QString target(dst + "/" + i.fileName());

        if (i.isFile()) {
            QFileInfo file(target);
            if (file.exists()) {
                if (file.birthTime() < i.birthTime()) {
                    QFile(target).remove();
                    qInfo() << "-->update"
                            << QFile::copy(i.absoluteFilePath(), target) << ": "
                            << i.absoluteFilePath() << " >> " << target;
                }
            } else {
                qInfo() << "-->copy"
                        << QFile::copy(i.absoluteFilePath(), target) << ": "
                        << i.absoluteFilePath() << " >> " << target;
            }
        } else if (i.isDir()) {
            if (!QDir(target).exists()) {
                QDir(dst).mkpath(i.fileName());
            }
            sync(i.absoluteFilePath(), target);
        }
        for (size_t j = 0; j < dst_file.size(); j++) {
            if (i.fileName() == dst_file[j].fileName()) {
                dst_file.removeAt(j);
                break;
            }
        }
    }

    for (auto& i : dst_file) {
        if (i.isDir()) {
            qInfo() << "-->delete"
                    << QDir(i.absoluteFilePath()).removeRecursively() << ": "
                    << i.absoluteFilePath();
        } else if (i.isFile()) {
            qInfo() << "-->delete" << QFile(i.absoluteFilePath()).remove()
                    << ": " << i.absoluteFilePath();
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOptions(
        { { "src", "src path", "src" }, { "dst", "dst path", "dst" } });
    parser.process(app);

    if (parser.isSet(QString("src")) && parser.isSet(QString("dst"))) {
        QString src_path = parser.value("src");
        QString dst_path = parser.value("dst");
        qInfo() << "src:  " << src_path;
        qInfo() << "dst:  " << dst_path;
        if (sync(src_path, dst_path)) {
            qInfo() << "successful";
        } else {
            qInfo() << "failed";
        }
    } else {
        qInfo() << "sorry, please set src path and dst path";
    }
    return QCoreApplication::exec();
}
