Übung 1
-------

Bei dieser Übung geht es darum Cucumber-cpp kennenzulernen und die ersten Step Definitionen zu implementieren. Sämtlicher Code kann direkt in den Step Definitionen implementiert werden und ihr solltet keine separaten Klassen/Komponenten unter Test implementieren. 
Im Verzeichnis tests/feature/features findet ihr ein Feature Datei (Calculator.feature) für welches noch keine Schritte definiert sind.

Schritte:
  1.  Mit CMake das Projekt konfigurieren, indem es:
    a.  in die DIE importiert wird (QtCreator, Eclipse, CLion)
    b.  eine Visual Studio Solution generiert wird.
      > md build
      > cd build
      > cmake –G“Visual Studio 14 2015“ ..

  2.  Externe Libraries builden:
    a.  build target external_dependencies (in IDE)
    b.  im projet root:
      > cmake –build build –target external_dependencies

  3.  Target  run_wip_features führt alle mit @wip markierte Scenarios aus

  4.  Step Definitionen für das erste Scenario implementieren.

  5.  Wenn das erste Scenario PASSED @wip tag entfernen

  6.  Target run_feature_test ausführen -> Muss Erfolgreich sein

  7.  Mit dem nächsten Scenario bei Schritt 3 weitermachen bis kein @wip Scenario mehr vorhanden ist und alle Scenarios Erfolgreich laufen.
