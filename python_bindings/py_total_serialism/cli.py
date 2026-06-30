# Main gui

from PyQt6.QtWidgets import QApplication

from .mainWindow import MainWindow

def main():
    app = QApplication([])
    window = MainWindow()
    window.show()

    app.exec()
