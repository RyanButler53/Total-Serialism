# Main gui

from PyQt6.QtWidgets import QApplication
from PyQt6.QtGui import QIcon
import os

from mainWindow import MainWindow,basedir

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.setWindowIcon(QIcon(os.path.join(basedir, 'icon.icns')))
    app.exec()
