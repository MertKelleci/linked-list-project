#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DOSYA "sehirler.txt"
#define CIKIS "sonuc.txt"
struct SehirList
{
    int plaka;
    char isim[50];
    char bolge[3];
    char komsular[200];
    int komsuSayisi;
    struct SehirList *next;
    struct SehirList *prev;
    struct Komsu *komsuilk;
    struct Komsu *komsuson;
};
struct Komsu
{
    int plaka;
    struct Komsu *next;
};

struct SehirList *ilk = NULL, *son=NULL;

void baslangic()
{
    int i,k=0,c;
    FILE *sehirler = fopen(DOSYA,"r");

    struct SehirList *yeni = (struct SehirList*)malloc(sizeof(struct SehirList));
    fscanf(sehirler,"%d",&yeni->plaka);
    char tut[101];
    fgets(tut,100,sehirler);
    for(i=0; i<sizeof(tut); i++)
        tut[i]=tut[i+1];
    //Ismi yeni structa yazdirir.
    for(i=0; tut[i]!=','; i++)
    {
        yeni->isim[k] = tut[i];
        k++;
    }
    yeni->isim[k]='\0';
    i++;
    k=0;

    //Bolgeyi yeni structa yazdirir.
    for(i; tut[i]!=','; i++)
    {
        yeni->bolge[k] = tut[i];
        k++;
    }
    yeni->bolge[k]='\0';
    i++;
    k=0;

    //Komuslarý olusturur.
    for(i; i<sizeof(tut); i++)
    {
        tut[k] = tut[i];
        k++;
    }

    strcpy(yeni->komsular,tut);
    yeni->komsuSayisi = 0;

    ilk=yeni;
    son=yeni;
    ilk->next=son;
    son->prev=ilk;
    ilk->komsuilk = NULL;
    ilk->komsuson = NULL;

    for(c=0; c<80; c++)
    {
        struct SehirList *yeni1 = (struct SehirList*)malloc(sizeof(struct SehirList));
        fscanf(sehirler,"%d",&yeni1->plaka);
        fgets(tut,100,sehirler);
        for(i=0; i<sizeof(tut); i++)
            tut[i]=tut[i+1];


        k=0;
        for(i=0; tut[i]!=','; i++)
        {
            yeni1->isim[k] = tut[i];
            k++;
        }
        yeni1->isim[k]='\0';
        i++;
        k=0;

        for(i; tut[i]!=','; i++)
        {
            yeni1->bolge[k] = tut[i];
            k++;
        }
        yeni1->bolge[k]='\0';
        i++;
        k=0;

        for(i; i<sizeof(tut); i++)
        {
            tut[k] = tut[i];
            k++;
        }

        strcpy(yeni1->komsular,tut);
        yeni1->komsuSayisi = 0;

        yeni1->prev = son;
        son->next = yeni1;
        son=yeni1;
        son->next = NULL;
        son->komsuilk = NULL;
        son->komsuson = NULL;
    }
    struct SehirList *run = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct SehirList *inrun = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct Komsu *sirala = (struct Komsu*)malloc(sizeof(struct Komsu));
    struct Komsu *gez = (struct Komsu*)malloc(sizeof(struct Komsu));
    run = ilk;
    char *ilisim = 'c';

    while(run!=NULL)
    {
        ilisim=strtok(run->komsular,",");
        while(ilisim!=NULL)
        {
            inrun = ilk;
            while(inrun!=NULL)
            {
                if(strstr(ilisim,inrun->isim)!=NULL)
                {
                    struct Komsu *yeniKomsu = (struct Komsu*)malloc(sizeof(struct Komsu));
                    yeniKomsu->plaka = inrun->plaka;
                    run->komsuSayisi++;

                    if(run->komsuilk == NULL)
                    {
                        run->komsuilk = yeniKomsu;
                        run->komsuson = yeniKomsu;
                        yeniKomsu->next = NULL;
                    }

                    else
                    {
                        run->komsuson->next = yeniKomsu;
                        run->komsuson = yeniKomsu;
                        yeniKomsu->next = NULL;
                    }

                }

                inrun = inrun->next;
            }
            ilisim=strtok(NULL,",");
        }

        sirala = run->komsuilk;
        gez = run->komsuilk;
        int temp;
        while(gez!=NULL)
        {
            sirala = run->komsuilk;
            while(sirala->next!=NULL)
            {
                if(sirala->plaka > sirala->next->plaka)
                {
                    temp = sirala->plaka;
                    sirala->plaka = sirala->next->plaka;
                    sirala->next->plaka = temp;
                }
                sirala = sirala->next;
            }
            gez = gez->next;
        }

        run = run->next;
    }
}

int SehirEkle()
{
    struct SehirList *yeni = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct SehirList *test = (struct SehirList*)malloc(sizeof(struct SehirList));
    test = ilk;
    printf("Eklemek istediginiz sehrin ismini girin:\n");
    scanf("%s",yeni->isim);

    while(test!=NULL)
    {
        if(strstr(yeni->isim,test->isim)!=NULL)
        {
            printf("Eklemek istediginiz sehrin ismi listede var olan bir sehrin ismiyle ayni!\n");
            return(0);
        }
        test = test->next;
    }

    printf("\nEklemek istediginiz sehrin bolge kodunu giriniz\n(Akdeniz (AK), Dogu Anadolu (DA), Ege (EG), Guneydogu Anadolu (GA),\n Ic Anadolu (IA), Marmara (MA) ve Karadeniz (KA))\n");
    scanf("%s",yeni->bolge);

    printf("\nEklemek istediginiz sehrin plakasini girin\n");
    scanf("%d",&yeni->plaka);

    test = ilk;

    while(test!=NULL)
    {
        if(yeni->plaka == test->plaka)
        {
            printf("Eklemek istedigniz sehrin plakasi listede var olan bir sehrin plakasi ile ayni!\n");
            return(0);
        }
        test = test->next;
    }
    yeni->next = NULL;
    yeni->komsuilk = NULL;
    yeni->komsuson = NULL;
    yeni->prev = NULL;

    if(test==NULL)
    {
        test = ilk;

        while(test->next != NULL)
        {
            if(yeni->plaka < test->next->plaka)
            {
                yeni->next = test->next;
                yeni->prev = test;
                test->next->prev = yeni;
                test->next = yeni;
                return(1);
            }

            test = test->next;
        }

        if(test == son)
        {
            son->next = yeni;
            yeni->prev = son;
            son = yeni;
        }
    }

    return(1);
}


int KomsuEkle(int a)
{
    struct SehirList *run = (struct SehirList*)malloc(sizeof(struct SehirList));
    run = ilk;
    int plaka;
    char Ad[50];

    if(a==1)
    {
        printf("Komsu eklemek istediginiz sehrin adini giriniz:\n");
        scanf("%s",Ad);

        while(run!=NULL)
        {
            if(strstr(run->isim,Ad)!=NULL)
                break;

            run = run->next;
        }
    }

    else if(a==2)
    {
        printf("Komsu eklemek istediginiz sehrin plakasini giriniz:\n");
        scanf("%d",&plaka);

        while(run!=NULL)
        {
            if(run->plaka == plaka)
                break;

            run = run->next;
        }
    }

    if(run == NULL)
    {
        printf("Girdiginiz sehir listede yoktur!\n");
        return 0;
    }

    int komsuPlaka = 1;
    struct SehirList *inrun = (struct SehirList*)malloc(sizeof(struct SehirList));
    do
    {
        switch(komsuPlaka)
        {
        case 0:
            return 0;
            break;


        default:
            printf("Komsu olarak eklemek istediginiz sehrin plakasini girin(Cikmak icin 0 girin):\n");
            scanf("%d",&komsuPlaka);
            struct Komsu *yeniKomsu = (struct Komsu*)malloc(sizeof(struct Komsu));
            yeniKomsu->plaka = komsuPlaka;
            if(run->komsuilk == NULL)
            {
                inrun=ilk;

                while(inrun!=NULL)
                {
                    if(inrun->plaka == komsuPlaka)
                    {
                        yeniKomsu->next = NULL;
                        run->komsuilk = yeniKomsu;
                        run->komsuson = yeniKomsu;
                        run->komsuSayisi++;
                        break;
                    }

                    inrun = inrun->next;
                }

                if(inrun == NULL)
                {
                    printf("Sehir listesinde %d plakali bir sehir yoktur!\n",komsuPlaka);
                    return 0;
                }
            }

            else
            {
                inrun = ilk;

                while(inrun!=NULL)
                {
                    if(inrun->plaka == komsuPlaka)
                    {
                        run->komsuson->next = yeniKomsu;
                        run->komsuson = yeniKomsu;
                        run->komsuson->next = NULL;
                        run->komsuSayisi++;
                        break;
                    }

                    inrun = inrun->next;
                }

                if(inrun == NULL)
                {
                    printf("Sehir listesinde %d plakali bir sehir yoktur!\n",komsuPlaka);
                    return 0;
                }

                else
                {
                    struct Komsu *gez = (struct Komsu*)malloc(sizeof(struct Komsu));
                    struct Komsu *sec = (struct Komsu*)malloc(sizeof(struct Komsu));
                    int temp;

                    gez = run->komsuilk;
                    while(gez!=NULL)
                    {
                        sec = run->komsuilk;
                        while(sec->next!=NULL)
                        {
                            if(sec->plaka > sec->next->plaka)
                            {
                                temp = sec->plaka;
                                sec->plaka = sec->next->plaka;
                                sec->next->plaka = temp;
                            }
                            sec = sec->next;
                        }
                        gez = gez->next;
                    }
                }


            }
        }
    }
    while(komsuPlaka!=0);
}

int SehirSil()
{
    struct SehirList *sehir = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct Komsu *komsu = (struct SehirList*)malloc(sizeof(struct Komsu));
    int secim;
    char Ad[50];
    int plaka;
    printf("Silmek istediginiz sehrin plakasini girin:\n");
    scanf("%d",&plaka);
    sehir = ilk;
    while(sehir!=NULL)
    {
        if(sehir->plaka == plaka)
        {
            if(sehir == ilk)
            {
                sehir->next->prev = NULL;
                ilk = sehir->next;
                free(sehir);
                return 1;
            }

            else if(sehir == son)
            {
                sehir->prev->next = NULL;
                son = sehir->prev;
                free(sehir);
                return 1;
            }

            else
            {
                sehir->prev->next = sehir->next;
                sehir->next->prev = sehir->prev;
                free(sehir);
                return 1;
            }
        }

        sehir = sehir->next;
    }

    if(sehir==NULL)
        printf("Silmek istediginiz sehir listede yoktur:\n");
}


int KomsuSil()
{
    struct SehirList *sehir = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct Komsu *komsu = (struct Komsu*)malloc(sizeof(struct Komsu));
    int plaka;
    int komsuPlaka=1;

    printf("Komsulugunu silmek istediginiz sehrin plaka kodunu girin:\n");
    scanf("%d",&plaka);
    sehir = ilk;

    while(sehir!=NULL)
    {
        if(sehir->plaka == plaka)
            break;

        sehir = sehir->next;
    }


    if(sehir == NULL)
    {
        printf("Komsuluklarini silmek istediginiz sehir listede yoktur!\n");
        return 0;
    }

    if(sehir->komsuSayisi == 0)
    {
        printf("Komsuluklarini silmek istediginiz sehirin hic komsunu yoktur!\n");
        return 0;
    }

    while(plaka != 0)
    {
        printf("Silmek istediginiz komsu ilin plakasini girin:(Cikmak icin 0 girin):\n");
        scanf("%d",&plaka);

        komsu = sehir->komsuilk;

        if(plaka == 0)
            komsu=NULL;

        while(komsu!=NULL)
        {
            if(sehir->komsuSayisi == 0)
            {
                printf("Sehrin komsusu kalmamistir!\n");
                return 1;
            }

            if(komsu == sehir->komsuilk && komsu->plaka == plaka)
            {
                sehir->komsuilk = sehir->komsuilk->next;
                sehir->komsuSayisi--;
                break;
            }
            else if(komsu->next->plaka == plaka)
            {
                if(komsu->next == sehir->komsuson)
                {
                    sehir->komsuson = komsu;
                    komsu->next = NULL;
                    sehir->komsuSayisi--;
                    break;
                }

                else if(komsu->next->plaka == plaka)
                {
                    komsu->next = komsu->next->next;
                    sehir->komsuSayisi--;
                    break;
                }
            }
            komsu = komsu->next;
        }
        if(komsu==NULL)
            printf("Silmek istediginiz komsuluk bulunmamaktadir!\n");
    }
}

void Yazdir()
{
    FILE *sonuc;
    if((sonuc = fopen(CIKIS,"a")) == NULL)
    {
        printf("Sonuc dosyasi olusturulamadi");
        return 0;
    }

    struct SehirList *sehir = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct Komsu *komsu = (struct Komsu*)malloc(sizeof(struct Komsu));

    sehir = ilk;
    fprintf(sonuc,"\n---Sehir Listesi---\n");

    while(sehir!=NULL)
    {
        fprintf(sonuc,"Sehir plakasi:\t%d\n",sehir->plaka);
        fprintf(sonuc,"Sehir ismi:\t%s\n",sehir->isim);
        fprintf(sonuc,"Sehir bolgesi:\t%s\n",sehir->bolge);
        fprintf(sonuc,"Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);
        fprintf(sonuc,"Sehir komsulari plakalari:\n");
        komsu = sehir->komsuilk;
        while(komsu!=NULL)
        {
            fprintf(sonuc,"-> ");
            fprintf(sonuc,"%d ",komsu->plaka);
            komsu = komsu->next;
        }
        fprintf(sonuc,"\n\n");
        sehir = sehir->next;
    }

    fclose(sonuc);
}

int OzelArama()
{
    FILE *sonuc;
    char Ad[50];
    char Bolge[3];
    struct SehirList *sehir = (struct SehirList*)malloc(sizeof(struct SehirList));
    struct Komsu *komsu = (struct Komsu*)malloc(sizeof(struct Komsu));
    int i;

    if((sonuc = fopen(CIKIS,"a")) == NULL)
    {
        printf("Sonuc dosyasi olusturulamadi");
        return 0;
    }

    int secim;
    int secimEkle;
    int plaka;
    int min;
    int max;
    printf("Gerceklestirmek istediginiz arama metodunu secin:\n");
    printf("1) Isme gore arama\n");
    printf("2) Plakaya gore arama\n");
    printf("3) Bolgeye gore arama(Akdeniz (AK), Dogu Anadolu (DA), Ege (EG), Guneydogu Anadolu (GA),\n Ic Anadolu (IA), Marmara (MA) ve Karadeniz (KA))\n");
    printf("4) Gireceginiz sayi ve fazlasi kadar komsusu olan sehirleri arama\n");
    printf("5) Belirli sayida komsu sayisi ve gireceginiz ortak komsusu olan illeri arama\n");
    scanf("%d",&secim);

    switch(secim)
    {
    case 1:
        printf("Isme gore arama...\nAranacak ismi girin:\n");
        scanf("%s",Ad);
        fprintf(sonuc,"Isme gore arama...(%s)\n",Ad);
        sehir = ilk;
        while(sehir!=NULL)
        {
            if(strstr(sehir->isim,Ad)!=NULL)
            {
                printf("Sehir plakasi:\t%d\n",sehir->plaka);
                fprintf(sonuc,"Sehir plakasi:\t%d\n",sehir->plaka);

                printf("Sehir ismi:\t%s\n",sehir->isim);
                fprintf(sonuc,"Sehir ismi:t\%s\n",sehir->isim);

                printf("Sehir bolgesi:\t%s\n",sehir->bolge);
                fprintf(sonuc,"Sehir bolgesi:\t%s\n",sehir->bolge);

                printf("Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);
                fprintf(sonuc,"Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);

                printf("Sehir komsu plakalari:\n");
                fprintf(sonuc,"Sehir komsu plakalari:\n");
                komsu = sehir->komsuilk;
                while(komsu!=NULL)
                {
                    printf("-> %d ",komsu->plaka);
                    fprintf(sonuc,"-> %d ",komsu->plaka);
                    komsu = komsu->next;
                }
                printf("\n\n");
                fprintf(sonuc,"\n\n");
                break;
            }
            sehir = sehir->next;
        }

        if(sehir==NULL)
        {
            printf("Aranilan sehir listede yok!\nEklemek istiyorsaniz 1'e, istemiyorsaniz 0'a basin\n");
            scanf("%d",&secimEkle);

            if(secim==1)
            {
                SehirEkle();
                break;
            }

            else if(secim==0);
            break;
        }

        break;

    ////////////////////////////////////////////////////////////

    case 2:
        printf("Plakaya gore arama...\nAranacak plakayi girin\n");
        scanf("%d",&plaka);
        fprintf(sonuc,"Plakaya gore arama...(%d)\n",plaka);

        sehir = ilk;

        while(sehir!=NULL)
        {
            if(sehir->plaka == plaka)
            {
                printf("Sehir plakasi:\t%d\n",sehir->plaka);
                fprintf(sonuc,"Sehir plakasi:\t%d\n",sehir->plaka);

                printf("Sehir ismi:\t%s\n",sehir->isim);
                fprintf(sonuc,"Sehir ismi:t\%s\n",sehir->isim);

                printf("Sehir bolgesi:\t%s\n",sehir->bolge);
                fprintf(sonuc,"Sehir bolgesi:\t%s\n",sehir->bolge);

                printf("Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);
                fprintf(sonuc,"Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);

                printf("Sehir komsu plakalari:\n");
                fprintf(sonuc,"Sehir komsu plakalari:\n");
                komsu = sehir->komsuilk;
                while(komsu!=NULL)
                {
                    printf("-> %d ",komsu->plaka);
                    fprintf(sonuc,"-> %d ",komsu->plaka);
                    komsu = komsu->next;
                }
                printf("\n\n");
                fprintf(sonuc,"\n\n");
                break;
            }
            sehir = sehir->next;
        }

        if(sehir==NULL)
        {
            printf("Aranilan sehir listede yok!\nEklemek istiyorsaniz 1'e, istemiyorsaniz 0'a basin\n");
            scanf("%d",&secimEkle);

            if(secim==1)
            {
                SehirEkle();
                break;
            }

            else if(secim==0);
            break;
        }

        break;
    ////////////////////////////////////////////////////
    case 3:
        printf("Bolgeye gore arama...\nAranacak bolgeyi girin:\n");
        scanf("%s",Bolge);
        fprintf(sonuc,"Bolgeye gore arama...(%s)\n",Bolge);

        sehir = ilk;

        while(sehir!=NULL)
        {
            if(strstr(sehir->bolge,Bolge)!=NULL)
            {
                printf("Sehir plakasi:\t%d\n",sehir->plaka);
                fprintf(sonuc,"Sehir plakasi:\t%d\n",sehir->plaka);

                printf("Sehir ismi:\t%s\n",sehir->isim);
                fprintf(sonuc,"Sehir ismi:t\%s\n",sehir->isim);

                printf("Sehir bolgesi:\t%s\n",sehir->bolge);
                fprintf(sonuc,"Sehir bolgesi:\t%s\n",sehir->bolge);

                printf("Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);
                fprintf(sonuc,"Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);

                printf("Sehir komsu plakalari:\n");
                fprintf(sonuc,"Sehir komsu plakalari:\n");
                komsu = sehir->komsuilk;
                while(komsu!=NULL)
                {
                    printf("-> %d ",komsu->plaka);
                    fprintf(sonuc,"-> %d ",komsu->plaka);
                    komsu = komsu->next;
                }
                printf("\n\n");
                fprintf(sonuc,"\n\n");
            }
            sehir = sehir->next;
        }
        break;
    /////////////////////////////////////////////////
    case 4:
        printf("Minimum komsu sayisini gore arama...\nMinimum sayiyi giriniz:\n");
        scanf("%d",&min);
        fprintf(sonuc,"Minimum komsu sayisina gore arama...(%d)",min);

        sehir = ilk;
        printf("\n");
        fprintf(sonuc,"\n");

        while(sehir!=NULL)
        {
            if(sehir->komsuSayisi>=min)
            {
                printf("Sehir plakasi:\t%d\n",sehir->plaka);
                fprintf(sonuc,"Sehir plakasi:\t%d\n",sehir->plaka);

                printf("Sehir ismi:\t%s\n",sehir->isim);
                fprintf(sonuc,"Sehir ismi:t\%s\n",sehir->isim);

                printf("Sehir bolgesi:\t%s\n",sehir->bolge);
                fprintf(sonuc,"Sehir bolgesi:\t%s\n",sehir->bolge);

                printf("Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);
                fprintf(sonuc,"Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);

                printf("Sehir komsu plakalari:\n");
                fprintf(sonuc,"Sehir komsu plakalari:\n");
                komsu = sehir->komsuilk;
                while(komsu!=NULL)
                {
                    printf("-> %d ",komsu->plaka);
                    fprintf(sonuc,"-> %d ",komsu->plaka);
                    komsu = komsu->next;
                }
                printf("\n\n");
                fprintf(sonuc,"\n\n");
            }
            sehir = sehir->next;
        }
        break;
    /////////////////////////////////////////////////////
    case 5:
        printf("Belirli komsudan fazla ve girilen sehirler ortak komsusu olma durumuna gore arama...\nMininum ve maksimum komsu sayisini girin:\n");
        fprintf(sonuc,"Belirli komsudan fazla ve girilen sehirler ortak komsusu olma durumuna gore arama...\n");
        scanf("%d %d",&min,&max);
        char Tugrul[50] = "Hebele";
        int nkomsu = 0;
        int nkomsu1 = 0;
        int *SearchKomsu = (int*)malloc(nkomsu*sizeof(int));
        while(strstr(Tugrul,"Cikis")==NULL)
        {
            printf("Komsuluk kosulu olan sehrin ismini girin:(Cikmak icin 'Cikis' girin)\n");
            scanf("%s",Tugrul);
            sehir = ilk;
            while(sehir!=NULL)
            {

                if(strstr(sehir->isim,Tugrul)!=NULL)
                {
                    SearchKomsu[nkomsu]=sehir->plaka;
                    nkomsu++;
                    SearchKomsu = (int*)realloc(SearchKomsu,nkomsu*sizeof(int));
                    sehir = sehir->next;
                    break;
                }
                sehir = sehir->next;
            }

            sehir = ilk;
        }


        sehir = ilk;
        while(sehir!=NULL)
        {
            komsu = sehir->komsuilk;
            nkomsu1 = 0;
            while(komsu!=NULL)
            {
                for(i=0; i<=nkomsu; i++)
                    if(komsu->plaka == SearchKomsu[i])
                        nkomsu1++;

                komsu = komsu->next;
            }

            if(nkomsu1 == nkomsu && sehir->komsuSayisi>=min && sehir->komsuSayisi<=max)
            {
                printf("Sehir plakasi:\t%d\n",sehir->plaka);
                fprintf(sonuc,"Sehir plakasi:\t%d\n",sehir->plaka);

                printf("Sehir ismi:\t%s\n",sehir->isim);
                fprintf(sonuc,"Sehir ismi:t\%s\n",sehir->isim);

                printf("Sehir bolgesi:\t%s\n",sehir->bolge);
                fprintf(sonuc,"Sehir bolgesi:\t%s\n",sehir->bolge);

                printf("Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);
                fprintf(sonuc,"Sehir komsu sayisi:\t%d\n",sehir->komsuSayisi);

                printf("Sehir komsu plakalari:\n");
                fprintf(sonuc,"Sehir komsu plakalari:\n");
                komsu = sehir->komsuilk;
                while(komsu!=NULL)
                {
                    printf("-> %d ",komsu->plaka);
                    fprintf(sonuc,"-> %d ",komsu->plaka);
                    komsu = komsu->next;
                }
                printf("\n\n");
                fprintf(sonuc,"\n\n");

            }

            sehir= sehir->next;
        }



        break;

    }

    fclose(sonuc);
}

int main()
{
    baslangic();
    int secim;
    int insecim;
    do
    {
        printf("-------MENU-------\n");
        printf("1) Sehir Ekle\n");
        printf("2) Komsu Ekle\n");
        printf("3) Sehir Silme\n");
        printf("4) Komsu Silme\n");
        printf("5) Ozel Arama\n");
        printf("0) Cikis\n");
        scanf("%d",&secim);

        switch(secim)
        {
        case 1:
            SehirEkle();
            break;

        case 2:
            printf("Komsu eklemek istediginiz ili ad olarak belirtecekseniz 1'e, plaka olarak belirtecekseniz 2'ye basim\n");
            scanf("%d",&insecim);
            KomsuEkle(insecim);
            break;

        case 3:
            SehirSil();
            break;

        case 4:
            KomsuSil();
            break;

        case 5:
            OzelArama();
            break;
        case 0:
            Yazdir();
            exit(1);
            break;
        }
    }
    while(secim!=0);

    return 0;
}

