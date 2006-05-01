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


#include "CompareExperimentsPanel.hxx"   // Change this to your new class header file name
#include "PanelContainer.hxx"   // Do not remove
#include "plugin_entry_point.hxx"   // Do not remove
#include "ArgumentObject.hxx"   // Do not remove

#include <qbuttongroup.h>

CompareExperimentsPanel::CompareExperimentsPanel(PanelContainer *pc, const char *n, ArgumentObject *ao) : CustomExperimentPanel(pc, n, ao, (const char *)"")
{

  hideWizard();



  // Hide the proceses control as we can't do anything anyway.
  frameLayout->remove(pco->buttonGroup);
  pco->buttonGroup->hide();
}


//! Destroys the object and frees any allocated resources
/*! The only thing that needs to be cleaned up is the baseWidgetFrame.
 */
CompareExperimentsPanel::~CompareExperimentsPanel()
{
}

bool
CompareExperimentsPanel::menu(QPopupMenu* contextMenu)
{
// printf("CompareExperimentsPanel::menu() entered\n");


  // If we've disabled this panel, don't allow any menus to be called.
  if( abortPanelFLAG == TRUE )
  {
    return TRUE;
  }

  contextMenu->insertSeparator();

  QAction *qaction = new QAction( this,  "EditName");
  qaction->addTo( contextMenu );
  qaction->setText( "Edit Panel Name..." );
  connect( qaction, SIGNAL( activated() ), this, SLOT( editPanelName() ) );
  qaction->setStatusTip( tr("Change the name of this panel...") );

  qaction = new QAction( this,  "CustomExperimentPanelSaveAs");
  qaction->addTo( contextMenu );
  qaction->setText( "Export Data..." );
  connect( qaction, SIGNAL( activated() ), this, SLOT( saveAsSelected() ) );
  qaction->setStatusTip( tr("Export data from all the CustomExperimentPanel's windows to an ascii file.") );

#if 0
  qaction = new QAction( this,  "expStatus");
  qaction->addTo( contextMenu );
  qaction->setText( "Experiment Status..." );
  connect( qaction, SIGNAL( activated() ), this, SLOT( experimentStatus() ) );
  qaction->setStatusTip( tr("Get general information about this experiment...") );
#endif // 0

  contextMenu->insertSeparator();

  qaction = new QAction( this,  "StatsPanel");
  qaction->addTo( contextMenu );
  qaction->setText( "Stats Panel..." );
  connect( qaction, SIGNAL( activated() ), this, SLOT( loadStatsPanel() ) );
  qaction->setStatusTip( tr("Bring up the data statistics for the experiment.") );

  qaction = new QAction( this,  "sourcePanel");
  qaction->addTo( contextMenu );
  qaction->setText( "Source Panel..." );
  connect( qaction, SIGNAL( activated() ), this, SLOT( loadSourcePanel() ) );
  qaction->setStatusTip( tr("Bring up the source panel.") );

  contextMenu->insertSeparator();

  qaction = new QAction( this,  "lsPanel");
  qaction->addTo( contextMenu );
  qaction->setText( QString("Open Experiment %1...").arg(leftSideExpID) );
  connect( qaction, SIGNAL( activated() ), this, SLOT( loadLSExperimentPanel() ) );
  qaction->setStatusTip( tr("Openss %1 experiment (left side) in it's own panel.") );

  qaction = new QAction( this,  "exp2Panel");
  qaction->addTo( contextMenu );
  qaction->setText( QString("Open Experiment %2...").arg(rightSideExpID) );
  connect( qaction, SIGNAL( activated() ), this, SLOT( loadRSExperimentPanel() ) );
  qaction->setStatusTip( tr("Openss %1 (right side) experiment in it's own panel.") );

  contextMenu->insertSeparator();

#if 0
  qaction = new QAction( this,  "customizeExperimentsSelected");
  qaction->addTo( contextMenu );
  qaction->setText( "Customize StatsPanel..." );
  connect( qaction, SIGNAL( activated() ), this, SLOT( customizeExperimentsSelected() ) );
  qaction->setStatusTip( tr("Customize column data in the StatsPanel.") );
#endif // 0

  return( TRUE );
}


void
CompareExperimentsPanel::hideWizard()
{
  QString name = "Compare Wizard";
// printf("try to find (%s)\n", name.ascii() );
  Panel *wizardPanel = getPanelContainer()->findNamedPanel(getPanelContainer()->getMasterPC(), (char *)name.ascii() );
  if( wizardPanel )
  {
//printf("Found the wizard... Try to hide it.\n");
    wizardPanel->getPanelContainer()->hidePanel(wizardPanel);
  }
}


void
CompareExperimentsPanel::loadLSExperimentPanel()
{
// printf("loadLSExperimentPanel() entered\n");
// printf("leftSideExpID=%d\n", leftSideExpID );
  getPanelContainer()->getMainWindow()->fileOpenExperiment(leftSideExpID);
}

void
CompareExperimentsPanel::loadRSExperimentPanel()
{
// printf("loadRSExperimentPanel() entered\n");
// printf("rightSideExpID=%d\n", rightSideExpID );

  getPanelContainer()->getMainWindow()->fileOpenExperiment(rightSideExpID);
}


int
CompareExperimentsPanel::listener(void *msg)
{
  int ret_val = CustomExperimentPanel::listener(msg);
  MessageObject *mo = (MessageObject *)msg;
// printf("mo->msgType=(%s)\n", mo->msgType.ascii() );
  if( mo->msgType  == "LoadAttachObject" )
  {
    QString name = QString("Stats Panel [%1]").arg(getExpID());
    LoadAttachObject *lao = (LoadAttachObject *)mo;
// printf("listener:: Try to find the stats panel =(%s)\n", name.ascii() );
// printf("lse=%s rse=%s\n", lao->leftSideExperiment.ascii(),  lao->leftSideExperiment.ascii() );
    Panel *p = getPanelContainer()->findNamedPanel(getPanelContainer(), (char *)name.ascii() );
    if( p )
    {
      p->getPanelContainer()->raisePanel(p);
    }
    name = QString("ManageProcessesPanel [%1]").arg(getExpID());
    p = getPanelContainer()->findNamedPanel(getPanelContainer(), (char *)name.ascii() );
    if( p )
    {
// printf("Try to delete the ManageProcessses panel.\n");
      p->getPanelContainer()->hidePanel( p );
    }

  }

  return( ret_val );
}
