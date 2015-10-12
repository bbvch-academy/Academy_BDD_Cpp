Übung 1
========

Bei dieser Übung geht es darum Cucumber-cpp kennenzulernen und die ersten Step Definitionen zu implementieren. Sämtlicher Code kann direkt in den Step Definitionen implementiert werden und es müssen keine separaten Klassen/Komponenten implementieren werden. 
Im Verzeichnis *tests/feature/features* findet ihr eine Feature Datei (Calculator.feature) für welches noch keine Schritte definiert sind.

## Schritte:
  1.  Mit CMake das Projekt konfigurieren, indem es:
    1.  in die IDE importiert wird (QtCreator, Eclipse, CLion)
    2.  eine Visual Studio Solution generiert wird.
      
      ```
      > md build
      > cd build
      > cmake -G"Visual Studio 14 2015" ..
      ```
  2.  Externe Libraries builden:
    1.  build target external_dependencies (in IDE)
    2.  im Projekt Root Verzeichnis:
      
      ```> cmake --build build --target external_dependencies```
  3.  Target *run_wip_features* führt alle mit @wip markierte Scenarios aus
  4.  Step Definitionen für das erste Scenario implementieren.
  5.  Wenn das erste Scenario PASSED @wip tag entfernen
  6.  Target *run_feature_test* ausführen -> Muss Erfolgreich sein
  7.  Mit dem nächsten Scenario bei Schritt 3 weitermachen bis kein @wip Scenario mehr vorhanden ist und alle Scenarios erfolgreich sind.
