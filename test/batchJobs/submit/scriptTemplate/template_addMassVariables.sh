#!/bin/bash

addMassVariables PATH_TO_CONFIGFILE/addMassVariables_"${SLURM_ARRAY_TASK_ID}"_cfg.py  # > PATH_TO_OUTJOBS/log_"${SLURM_ARRAY_TASK_ID}"

