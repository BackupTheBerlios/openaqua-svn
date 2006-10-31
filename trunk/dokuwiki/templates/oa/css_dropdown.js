function enableDropdownMenuForIE()
{
    if (document.all)
	{
        uls = document.getElementsByTagName('UL');

        for(i = 0; i < uls.length; i++)
        {
            if (uls[i].className == 'dropdown')
            {
                var lis = uls[i].getElementsByTagName('li');

                for (j = 0; j < lis.length; j++)
                {
                    if(lis[j].lastChild.tagName == 'UL')
                    {
                        lis[j].onmouseover = function() { this.lastChild.style.display = 'block'; }
                        lis[j].onmouseout = function() { this.lastChild.style.display = 'none'; }
                    }
                }
            }
        }
    }
}
