void ingres_def(void)
{
    putenv("II_SYSTEM=/dbsystem/II");
    putenv("LD_LIBRARY_PATH=/lib:/usr/lib:$II_SYSTEM/ingres/lib");
}

