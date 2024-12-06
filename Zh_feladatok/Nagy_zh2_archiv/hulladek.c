typedef struct {
	enum { ALTALANOS, EPITESI } tipus;
	double tartalom;
} kontener;


int atrendez(kontener tomb[], int meret)
{
    int kiuritett = 0;

    for (int i = 0; i < meret; i++)
    {
        if (tomb[i].tartalom == 0)
            continue;

        for (int j = meret - 1; j > i; j--)
        {
            if (tomb[j].tipus == ALTALANOS || (tomb[j].tipus == EPITESI && tomb[i].tipus == EPITESI))
            {
                double hely = 10.0 - tomb[j].tartalom;
                double atpakolhato = tomb[i].tartalom < hely ? tomb[i].tartalom : hely;

                tomb[j].tartalom += atpakolhato;
                tomb[i].tartalom -= atpakolhato;

                if (tomb[i].tartalom == 0)
                {
                    kiuritett++;
                    break;
                }
            }
        }
    }

    return kiuritett;
}