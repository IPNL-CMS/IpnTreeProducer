#!/bin/bash
# Script to create THE BIG PDF with all plots
# Written by O. Bondu (June 2010)

CMSSW_release="CMSSW_3_5_8_patch3"

syntax="Syntax ${0} {directory}"

if [[ -z ${1} ]]
then
  echo ${syntax}
  exit 1
fi

directory=${1}
directoryWOunderscores=`echo ${directory} | sed -e 's/_/\\\_/g'`

cd ${directory}

echo "
\documentclass{beamer}

\usepackage[english]{babel}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{graphicx}
\usepackage{colortbl}
\usepackage{wasysym}
\usepackage[abs]{overpic}
\usepackage{hyperref}

\setcounter{tocdepth}{1}

\title{SuperClusters DATA/MC comparisons\\${directoryWOunderscores}}
\author{IPN Lyon group}
\institute{IPN Lyon}

\begin{document}


\begin{frame}
\titlepage
\end{frame}


" > presentation_${directory}.tex

# ******************** SuperClusters
echo "\section{SuperClusters}" >> presentation_${directory}.tex


echo "
\subsubsection{Multiplicity}
\begin{frame}
\begin{center}
SuperClusters: Multiplicity\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_Multiplicity_NoCuts.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_Multiplicity_isAfterCut3_NoCuts.pdf}
\\
\footnotesize
\hspace{.36\textwidth}before selection\hspace{.36\textwidth}after selection
\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_Multiplicity_NoCuts_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_Multiplicity_isAfterCut3_NoCuts_log.pdf}
\\
\end{center}
\end{frame}" >> presentation_${directory}.tex


for cut in `echo "isAfterCut3 isAfterCut3_RawEtGT2 isAfterCut3_RawEtGT4 isAfterCut3_RawEtGT10"`
do
	Cut=`echo "${cut}" | sed -e 's/_/ /g'`
echo "
\subsection{${Cut}}
\begin{frame}
\begin{center}\Huge
	SuperClusters: ${Cut}
\end{center}
\end{frame}
" >> presentation_${directory}.tex
	for variable in `echo "E Et RawE RawEt Eta Phi etaWidth phiWidth"`
	do
		echo "
\subsubsection{${variable}}
\begin{frame}
\begin{center}
	SuperClusters: ${Cut}, ${variable}\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EB.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE.pdf}
\\
all\hspace{.36\textwidth}EB\hspace{.36\textwidth}EE
\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EB_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE_log.pdf}
\end{center}
\end{frame}
\begin{frame}
\begin{center}
	SuperClusters: ${Cut}, ${variable}\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEM.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEP.pdf}
\\
EE\hspace{.36\textwidth}EEM\hspace{.36\textwidth}EEP
\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EE_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEM_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_SuperClu_${variable}_${cut}_EEP_log.pdf}
\end{center}
\end{frame}
" >> presentation_${directory}.tex
	done
done


# ********************* Photons
echo "\section{Photons}" >> presentation_${directory}.tex

for cut in `echo "isAfterCut7"`
do
echo "
\subsection{${cut}}
\begin{frame}
\begin{center}\Huge
	Photons: ${cut}
\end{center}
\end{frame}" >> presentation_${directory}.tex

echo "
\subsubsection{Multiplicity}
\begin{frame}
\begin{center}
Photons: Multiplicity\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_Multiplicity_NoCuts.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_Multiplicity_isAfterCut7_NoCuts.pdf}
\\
\hspace{.36\textwidth}before selection\hspace{.36\textwidth}after selection
\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_Multiplicity_NoCuts_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_Multiplicity_isAfterCut7_NoCuts_log.pdf}
\end{center}
\end{frame}

\begin{frame}
\begin{center}
Photons: Multiplicity\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_Multiplicity_isAfterCut7_NoCuts.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_nPhotonEB_perEvent_NoCuts.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_nPhotonEE_perEvent_NoCuts.pdf}
\\
all\hspace{.36\textwidth}EB\hspace{.36\textwidth}EE
\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_Multiplicity_isAfterCut7_NoCuts_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_nPhotonEB_perEvent_NoCuts_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_nPhotonEE_perEvent_NoCuts_log.pdf}
\end{center}
\end{frame}" >> presentation_${directory}.tex


#  for variable in `echo "E Et Eta Phi SCEnergy SCEt SCRawEnergy SCRawEt covIetaIeta covIphiIphi etaWidth phiWidth"`
  for variable in `echo "Eta Phi SCEta SCPhi hasPixelSeed isAlsoElectron Nclusters nXtals E Et SCEnergy SCEt SCRawEnergy SCRawEt PreshEnergy E5x5 E3x3 E2x2 Emax E2nd r19 r9 cross caloConeSize covIetaIeta covIphiIphi etaWidth phiWidth isoEcalRecHit isoHcalRecHit HoE isoSolidTrkCone isoHollowTrkCone isoNTracksSolidCone isoNTracksHollowCone convNTracks seedTime seedFlag seedSeverity isTightPhoton isLoosePhoton"`
  do
    echo "
\subsubsection{${variable}}
\begin{frame}
\begin{center}
	Photons: ${cut}, ${variable}\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EB.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE.pdf}
\\
all\hspace{.36\textwidth}EB\hspace{.36\textwidth}EE
\\
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EB_log.pdf}
\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE_log.pdf}
\end{center}
\end{frame}
%\begin{frame}
%\begin{center}
%	Photons: ${cut}, ${variable}\\
%\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE.pdf}
%\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEM.pdf}
%\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEP.pdf}
%\\
%EE\hspace{.36\textwidth}EEM\hspace{.36\textwidth}EEP
%\\
%\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EE_log.pdf}
%\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEM_log.pdf}
%\includegraphics[width=.36\textwidth]{pdf/DataMC_Photon_${variable}_${cut}_EEP_log.pdf}
%\end{center}
%\end{frame}
" >> presentation_${directory}.tex
  done
done


echo "

\end{document}
" >> presentation_${directory}.tex


echo "Creating the pdf with pdflatex"
pdflatex presentation_${directory}.tex
pdflatex presentation_${directory}.tex
pdflatex presentation_${directory}.tex

exit 0





