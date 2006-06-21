////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////


#ifndef STATSPANEL_H
#define STATSPANEL_H
#include "SPListView.hxx"           // Do not remove
#include "Panel.hxx"           // Do not remove
#include "CollectorListObject.hxx"
#include "GenericProgressDialog.hxx"
#include "SelectTimeSegmentDialog.hxx"

#include "ToolAPI.hxx"
#include "Queries.hxx"

using namespace OpenSpeedShop;
using namespace OpenSpeedShop::Framework;

class PanelContainer;   // Do not remove
class QVBoxLayout;
class QHBoxLayout;
class QFile;
class GenericProgressDialog;
class SourceObject;
class QToolBar;
#include "SPChartForm.hxx"
#include "HighlightObject.hxx"


#include <qlistview.h>
#include <qsplitter.h>
#include <qpopupmenu.h>
#include <qinputdialog.h>

#include "CollectorInfo.hxx"   // For dummied up data...

#include "SPListViewItem.hxx"


#include "ArgumentObject.hxx"
#include "SS_Input_Manager.hxx"

#include <qvaluelist.h>
typedef QValueList<QString> FieldList;
typedef QValueList<QString> ColumnList;
typedef QValueList<QString> ThreadGroupStringList;
typedef QValueList<QString> ExperimentGroupList;

typedef std::pair<Function, double> Function_double_pair;
typedef std::pair<Function, unsigned int> Function_uint_pair;
typedef std::pair<Function, uint64_t> Function_uint64_pair;

#include <qsettings.h>
#include <qtimer.h>

enum CURRENTTHREADSTR_ENUM { UNKNOWN, RANK,  THREAD, PID };


class CInfoClass
{
  public:
    CInfoClass( ) { };
    CInfoClass( int _cid, QString _collector_name, int _expID, QString _host_pid_names, QString _metricStr) { cid = _cid; collector_name = _collector_name, expID = _expID; host_pid_names = _host_pid_names; metricStr = _metricStr; };
//    ~CInfoClass() { printf("CInfoClass() Destructor called!\n"); } ;
    ~CInfoClass() { } ;

    void print() { printf("%d %s %d %s %s\n", cid, collector_name.ascii(), expID, host_pid_names.ascii(), metricStr.ascii() ); };

    int cid;
    QString collector_name;
    int expID;
    QString host_pid_names;
    QString metricStr;
};
typedef QValueList<CInfoClass *> CInfoClassList;

class ColumnValueClass
{
  public:
    ColumnValueClass( ) { };
    ~ColumnValueClass( ) { };
    void init() { start_index = -1; end_index = -1; cic = NULL; };

    int start_index;
    int end_index;

    CInfoClass *cic;

    void print()
    {
      cout << start_index << " " << end_index << "\n";
      cic->print();
    }
};
typedef QValueList<ColumnValueClass *> ColumnValueClassList;



#define PANEL_CLASS_NAME StatsPanel   // Change the value of the define
//! StatsPanel Class
class StatsPanel  : public Panel
{
    //! Q_OBJECT is needed as there are slots defined for the class
    Q_OBJECT
  public:
    //! StatsPanel(PanelContainer *pc, const char *name)
    StatsPanel(PanelContainer *pc, const char *n, ArgumentObject *ao);

    //! ~StatsPanel() - The default destructor.
    ~StatsPanel();  // Active destructor

    //! Calls the user panel function listener() request.
    int listener(void *msg);

    //! Adds use panel menus (if any).
    virtual bool menu(QPopupMenu* contextMenu);

    //! Routine to popup dynamic menu.
    bool createPopupMenu( QPopupMenu* contextMenu, const QPoint &pos );

    InputLineObject *statspanel_clip;
    void process_clip(InputLineObject *statspanel_clip, HighlightList *highlightList, bool dumpClipFLAG);
    GenericProgressDialog *pd;
    SelectTimeSegmentDialog *timeSegmentDialog;
    QString timeIntervalString;
    QTimer *progressTimer;
    bool insertDiffColumnFLAG;
    bool absDiffFLAG;
    void insertDiffColumn(int insertAtIndex=0);
    void removeDiffColumn(int removeIndex);

    int focusedExpID;
    ExperimentGroupList experimentGroupList;
    CInfoClassList cInfoClassList;

    void analyzeTheCView();
    bool canWeDiff();

    SPListView *splv;

    QString lastAbout;
    QString aboutOutputString;
    QString about;
    QString originalCommand;
    QString lastCommand;
    bool staticDataFLAG;

    QVBoxLayout *frameLayout;
QToolBar * fileTools;
    QSplitter *splitterA;
    SPChartForm *cf;
    ColumnList columnHeaderList;
    ChartPercentValueList skylineValues;
    ChartTextValueList skylineText;
    FieldList columnFieldList;
    ColumnValueClass columnValueClass[80];
    int *metricHeaderTypeArray;  // matches the QListView # of column entries.

    std::list<std::string> list_of_collectors_metrics;
    std::list<std::string> list_of_collectors;
    std::list<int64_t> list_of_pids;
    std::list<std::string> list_of_modifiers;
    std::list<std::string> current_list_of_modifiers;

    std::list<std::string> list_of_mpi_modifiers;
    std::list<std::string> current_list_of_mpi_modifiers;
    std::list<std::string> list_of_mpit_modifiers;
    std::list<std::string> current_list_of_mpit_modifiers;
    std::list<std::string> list_of_io_modifiers;
    std::list<std::string> current_list_of_io_modifiers;
    std::list<std::string> list_of_iot_modifiers;
    std::list<std::string> current_list_of_iot_modifiers;
    std::list<std::string> list_of_hwc_modifiers;
    std::list<std::string> current_list_of_hwc_modifiers;
    std::list<std::string> list_of_hwctime_modifiers;
    std::list<std::string> current_list_of_hwctime_modifiers;
    std::list<std::string> list_of_pcsamp_modifiers;
    std::list<std::string> current_list_of_pcsamp_modifiers;
    std::list<std::string> list_of_usertime_modifiers;
    std::list<std::string> current_list_of_usertime_modifiers;
    std::list<std::string> list_of_fpe_modifiers;
    std::list<std::string> current_list_of_fpe_modifiers;
    std::list<std::string> list_of_generic_modifiers;
    std::list<std::string> current_list_of_generic_modifiers;

    void updateThreadsList();
    void updateCollectorList();
    void updateCollectorMetricList();
    void outputAboutData(QString *data);
    void outputCLIData(QString xxxfuncName, QString xxxfileName, int xxxlineNumber);
    bool MPItraceFLAG;
    bool IOtraceFLAG;

  protected:
    //! Sets the language specific strings.
    virtual void languageChange();

    //! Holds the current thread that is in focus
    Thread *currentThread;
    void setCurrentThread();

    ThreadGroupStringList currentThreadGroupStrList;

    //! Holds the current collector that is in focus
    Collector *currentCollector;
    void setCurrentCollector();

    QString currentMetricStr;
    void setCurrentMetricStr();
    QString currentUserSelectedReportStr;

    //! Current selected chart item.
    SPListViewItem *currentItem;
    int currentItemIndex;

    QPopupMenu *threadMenu;
    QPopupMenu *modifierMenu;

    QPopupMenu *mpiModifierMenu;
    QPopupMenu *mpitModifierMenu;
    QPopupMenu *ioModifierMenu;
    QPopupMenu *iotModifierMenu;
    QPopupMenu *hwcModifierMenu;
    QPopupMenu *hwctimeModifierMenu;
    QPopupMenu *pcsampModifierMenu;
    QPopupMenu *usertimeModifierMenu;
    QPopupMenu *fpeModifierMenu;
    QPopupMenu *genericModifierMenu;

    QPopupMenu *popupMenu;   // Pointer to the contextMenu
    QPopupMenu *mpi_menu;
    QPopupMenu *io_menu;
    QPopupMenu *hwc_menu;
    QPopupMenu *hwctime_menu;
    QPopupMenu *usertime_menu;
    QPopupMenu *pcsamp_menu;
    QPopupMenu *fpe_menu;
    QPopupMenu *generic_menu;

    QPopupMenu *experimentsMenu;

    QString currentThreadStr;
    CURRENTTHREADSTR_ENUM currentThreadStrENUM;
    QString currentThreadsStr;
    QString currentCollectorStr;
    QString collectorStrFromMenu;

    QFile *f;
    void generateToolBar();
    QLabel *toolbar_status_label;

#ifdef OLDWAY // move back to public slots:
    void headerSelected( int );
#endif // OLDWAY
  public slots:
    void itemSelected( QListViewItem * );
    void returnPressed( QListViewItem * );
    void itemSelected( int );
    void doOption(int id);
    void exportData();
    void details();
    void originalQuery();
    void cviewQueryStatements();
    void updatePanel();
    void focusOnExp(int);
    void gotoSource(bool use_current_item = FALSE);
    void aboutSelected();
    void MPItraceSelected();
    void IOtraceSelected();
    void customizeExperimentsSelected();
    void clusterAnalysisSelected();
    void manageProcessesSelected();
    void progressUpdate();

// TOOLBAR SLOTS
    void functionsSelected();
    void linkedObjectsSelected();
    void statementsSelected();
    void statementsByFunctionSelected();
    void calltreesSelected();
    void calltreesByFunctionSelected();
    void calltreesFullStackSelected();
    void calltreesFullStackByFunctionSelected();
    void tracebacksSelected();
    void tracebacksByFunctionSelected();
    void tracebacksFullStackSelected();
    void tracebacksFullStackByFunctionSelected();
    void butterflySelected();

  private slots:
    void threadSelected(int);
    void modifierSelected(int);
    void mpiModifierSelected(int);
    void mpitModifierSelected(int);
    void ioModifierSelected(int);
    void iotModifierSelected(int);
    void hwcModifierSelected(int);
    void hwctimeModifierSelected(int);
    void genericModifierSelected(int);
    void pcsampModifierSelected(int);
    void usertimeModifierSelected(int);
    void fpeModifierSelected(int);
    void collectorMetricSelected(int);
    void collectorMPIReportSelected(int);
    void collectorMPITReportSelected(int);
    void collectorIOReportSelected(int);
    void collectorIOTReportSelected(int);
    void collectorHWCReportSelected(int);
    void collectorHWCTimeReportSelected(int);
    void collectorUserTimeReportSelected(int);
    void collectorPCSampReportSelected(int);
    void collectorFPEReportSelected(int);
    void collectorGenericReportSelected(int);
    void showStats();
    void showDiff();
    void showChart();
    void setOrientation();

    void timeSliceSelected();

  private:
    bool matchSelectedItem( QListViewItem *item, std::string function_name );

    void updateStatsPanelData(QString command = QString::null);
    void generateMPIMenu(QString collectorName);
    void addMPIReports(QPopupMenu *menu);
    void generateIOMenu(QString collectorName);
    void addIOReports(QPopupMenu *menu);
    void generateHWCMenu(QString collectorName);
    void addHWCReports(QPopupMenu *menu);
    void generateHWCTimeMenu(QString collectorName);
    void addHWCTimeReports(QPopupMenu *menu);
    void generateUserTimeMenu();
    void addUserTimeReports(QPopupMenu *menu);
    void generatePCSampMenu();
    void addPCSampReports(QPopupMenu *menu);
    void generateFPEMenu();
    void addFPEReports(QPopupMenu *menu);
    void generateGenericMenu();
    QString generateCommand();
    void generateModifierMenu(QPopupMenu *, std::list<std::string>current_list, std::list<std::string>current_local_list);


    void MPIReportSelected(int);
    void IOReportSelected(int);
    void HWCReportSelected(int);
    void HWCTimeReportSelected(int);
    void resetRedirect();

    SPListViewItem *lastlvi;
    int lastIndentLevel;
    bool gotHeader;
    bool gotColumns;
    int fieldCount;
    int percentIndex;
    void raisePreferencePanel();

    int levelsToOpen;

    int steps;

    double TotalTime;
    double total_percent;
    int numberItemsToDisplayInStats;
    int numberItemsToDisplayInChart;
    char **color_names;
    ChartTextValueList ctvl;
    ChartPercentValueList cpvl;

    double double_minTime;
    double double_maxTime;
    unsigned int ui_minTime;
    unsigned int ui_maxTime;
    uint64_t uint64_minTime;
    uint64_t uint64_maxTime;

    int getLineColor(double value);
    int getLineColor(unsigned int value);
    int getLineColor(uint64_t value);


    QString getFilenameFromString( QString ); 
    QString getFunctionNameFromString( QString, QString & );

    bool descending_sort;

    int expID;

    //! Flag setting, indicating if we should be displaying the statistics.
    bool statsFLAG;

    //! Flag setting, indicating if we should be displaying the text in graphics.
    int textENUM;
  
    //! Flag setting, indicating if we should be displaying the chart.
    bool chartFLAG;

    CollectorListObject *clo;


    QString findSelectedFunction();
    QString selectedFunctionStr;

    SPListViewItem *MYListViewItem( StatsPanel *arg1, QString xxxfuncName, QString xxxfileName, int xxxlineNumber, SPListViewItem *arg2, SPListViewItem *arg3, QString *strings);

    SPListViewItem *MYListViewItem( StatsPanel *arg1, QString xxxfuncName, QString xxxfileName, int xxxlineNumber, QListView *arg2, SPListViewItem *arg3, QString *strings);

    SourceObject *lookUpFileHighlights(QString filename, QString lineNumberStr, HighlightList *highlightList);

};
#endif // STATSPANEL_H
