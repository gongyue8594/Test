//CMCC Manu-all-dial data load.
void probemanu_all_cmcc(void *udata)
{
	content_t *cn = (content_t *)udata;
	LOG(LOG_INFO, "Start cmcc manu-all probe.\n");
	char pesq[24] = {"\0"};
	int ret = 0;
	//probehand_all_task临时手动顺序拨测
	if(0 == probehand_all_task(cn, cn->cmcc))
	{
        cn->sql2->DIAL = 0;
		sprintf(cn->sql2->CMCC_MOS,"0");
		sprintf(cn->sql2->CMCC_FILE," ");
	}
	else
	{
	    cn->sql2->DIAL = 1;
	    memcpy(cn->sql2->CMCC_FILE, cn->cmcc->path, strlen(cn->cmcc->path));
	    //pesq
	    pthread_mutex_lock(&cn->key);
	  #ifndef test_gy
        printf("pesqfile path=%s, cn->cmcc->path=%s\n",cn->indexs[policyid].pesqfile, cn->cmcc->path);
      #endif
	    LOG(LOG_INFO, "START PESQ: %s==%s\n", cn->indexs[policyid].pesqfile, cn->cmcc->path);
	    ret = pesq_main("+16000", cn->indexs[policyid].pesqfile, cn->cmcc->path, pesq);
	    usleep(100);
        if (1 != ret)
		{
            pthread_mutex_unlock(&cn->key);
            cn->index_lt = cn->index_bt;
	        cn->hand = 0;
	        cn->action--;
	        cn->pstat = PROBE_IDLE;
        }
	    LOG(LOG_INFO,"PESQ:%s\n",pesq);
	    pthread_mutex_unlock(&cn->key);
	    LOG(LOG_INFO, "PESQ RES MOS:%s, wight:%d, pesqfile:%s, cmcc file:%s\n", pesq, cn->indexs[policyid].point, cn->indexs[policyid].pesqfile, cn->cmcc->path);
        ftppath_t *ftp = (ftppath_t *)calloc(sizeof(ftppath_t), 1);
	    memcpy(ftp->file, cn->sql2->CMCC_FILE, strlen(cn->sql2->CMCC_FILE));
	    memcpy(ftp->path, cn->indexs[policyid].uppath, strlen(cn->indexs[policyid].uppath));
        if (atoi(pesq) - cn->indexs[policyid].point >= 0)
        {
            LOG(LOG_INFO, "cmcc mos large, remove file %s.\n", cn->cmcc->path);
	        memset(cn->sql2->CMCC_FILE, 0, sizeof(cn->sql2->CMCC_FILE));
			memcpy(cn->sql2->CMCC_FILE, cn->cmcc->path, strlen(cn->cmcc->path));
	        ftp_upload((void *)ftp);
			printf("ftp upload file.\n");
    	}
		else
		{
			LOG(LOG_INFO, "cmcc mos er, upload file %s.\n", cn->cmcc->path);
			ftp_upload((void *)ftp);
		}
	}
	cn->index_lt = cn->index_bt;
    cn->hand = 0;
    cn->action--;
    cn->pstat = PROBE_IDLE;
	LOG(LOG_INFO, "Manu-all cmcc dial finished, will start sqlload.\n");
}
//COMC Manu-all-dial data load.
void probemanu_all_comc(void *udata)
{
	content_t *cn = (content_t *)udata;
	LOG(LOG_INFO, "Start comc manu-all probe.\n");
	char pesq[24] = {"\0"};
	int ret = 0;
	//probehand_all_task临时手动顺序拨测
	if(0 == probehand_all_task(cn, cn->comc))
	{
        cn->sql2->DIAL1 = 0;
		sprintf(cn->sql2->COMC_MOS,"0");
		sprintf(cn->sql2->COMC_FILE," ");
	}
	else
	{
	    cn->sql2->DIAL1 = 1;
		memcpy(cn->sql2->COMC_FILE, cn->comc->path, strlen(cn->comc->path));
		//pesq
		pthread_mutex_lock(&cn->key);
		#ifndef test_gy
	       printf("pesqfile path=%s, cn->comc->path=%s\n",cn->indexs[policyid].pesqfile, cn->comc->path);
	    #endif
		LOG(LOG_INFO, "START PESQ: %s==%s\n", cn->indexs[policyid].pesqfile, cn->comc->path);
		ret = pesq_main("+16000", cn->indexs[policyid].pesqfile, cn->comc->path, pesq);
		usleep(100);
	    if (1 != ret) {
	        pthread_mutex_unlock(&cn->key);
	        cn->index_lt = cn->index_bt;
		    cn->hand = 0;
		    cn->action--;
		    cn->pstat = PROBE_IDLE;
	    }
		LOG(LOG_INFO,"PESQ:%s\n",pesq);
		pthread_mutex_unlock(&cn->key);
		LOG(LOG_INFO, "PESQ RES MOS:%s, wight:%d, pesqfile:%s, comc file:%s\n", pesq, cn->indexs[policyid].point, cn->indexs[policyid].pesqfile, cn->comc->path);
	    ftppath_t *ftp = (ftppath_t *)calloc(sizeof(ftppath_t), 1);
		memcpy(ftp->file, cn->sql2->COMC_FILE, strlen(cn->sql2->COMC_FILE));
		memcpy(ftp->path, cn->indexs[policyid].uppath, strlen(cn->indexs[policyid].uppath));
	    if (atoi(pesq) - cn->indexs[policyid].point >= 0)
	    {
	        LOG(LOG_INFO, "comc mos large, remove file %s.\n", cn->comc->path);
	        memset(cn->sql2->COMC_FILE, 0, sizeof(cn->sql2->COMC_FILE));
			memcpy(cn->sql2->COMC_FILE, cn->comc->path, strlen(cn->comc->path));
	        ftp_upload((void *)ftp);
			printf("ftp upload file.\n");
	    }
		else
		{
			LOG(LOG_INFO, "comc mos er, upload file %s.\n", cn->comc->path);
			ftp_upload((void *)ftp);
		}
	}
	cn->index_lt = cn->index_bt;
    cn->hand = 0;
    cn->action--;
    cn->pstat = PROBE_IDLE;
	LOG(LOG_INFO, "Manu-all comc dial finished, will start sqlload.\n");
}
//CDMA Manu-all-dial data load.
void probemanu_all_cdma(void *udata)
{
	content_t *cn = (content_t *)udata;
	LOG(LOG_INFO, "Start cdma manu-all probe.\n");
	char pesq[24] = {"\0"};
	int ret = 0;
	//probehand_all_task临时手动顺序拨测
	if(0 == probehand_all_task(cn, cn->cdma))
	{
        cn->sql2->DIAL2 = 0;
		sprintf(cn->sql2->CDMA_MOS,"0");
		sprintf(cn->sql2->CDMA_FILE," ");
	}
	else
	{
	    cn->sql2->DIAL2 = 1;
		memcpy(cn->sql2->CDMA_FILE, cn->cdma->path, strlen(cn->cdma->path));
		//pesq
		pthread_mutex_lock(&cn->key);
		#ifndef test_gy
	       printf("pesqfile path=%s, cn->cdma->path=%s\n",cn->indexs[policyid].pesqfile, cn->cdma->path);
	    #endif
		LOG(LOG_INFO, "START PESQ: %s==%s\n", cn->indexs[policyid].pesqfile, cn->cdma->path);
		ret = pesq_main("+16000", cn->indexs[policyid].pesqfile, cn->cdma->path, pesq);
		usleep(100);
	    if (1 != ret)
		{
	        pthread_mutex_unlock(&cn->key);
	        cn->index_lt = cn->index_bt;
		    cn->hand = 0;
		    cn->action--;
		    cn->pstat = PROBE_IDLE;
	    }
		LOG(LOG_INFO,"PESQ:%s\n",pesq);
		pthread_mutex_unlock(&cn->key);
		LOG(LOG_INFO, "PESQ RES MOS:%s, wight:%d, pesqfile:%s, cdma file:%s\n", pesq, cn->indexs[policyid].point, cn->indexs[policyid].pesqfile, cn->cdma->path);
	    ftppath_t *ftp = (ftppath_t *)calloc(sizeof(ftppath_t), 1);
		memcpy(ftp->file, cn->sql2->CDMA_FILE, strlen(cn->sql2->CDMA_FILE));
		memcpy(ftp->path, cn->indexs[policyid].uppath, strlen(cn->indexs[policyid].uppath));
	    if (atoi(pesq) - cn->indexs[policyid].point >= 0)
	    {
	        LOG(LOG_INFO, "cdma mos large, remove file %s.\n", cn->cdma->path);
	        memset(cn->sql2->CDMA_FILE, 0, sizeof(cn->sql2->CDMA_FILE));
			memcpy(cn->sql2->CDMA_FILE, cn->cdma->path, strlen(cn->cdma->path));
	        ftp_upload((void *)ftp);
			printf("ftp upload file.\n");
	    }
		else
		{
			LOG(LOG_INFO, "cdma mos er, upload file %s.\n", cn->cdma->path);
			ftp_upload((void *)ftp);
		}
	}
	cn->index_lt = cn->index_bt;
    cn->hand = 0;
    cn->action--;
    cn->pstat = PROBE_IDLE;
	LOG(LOG_INFO, "Manu-all cdma dial finished, will start sqlload.\n");
}