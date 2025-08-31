ll power(ll base,ll p)
{
    ll res=1;
    while(p)
    {
        if(p%2==1)
        {
            res=(res*base)%mod;
            p--;
        }
        else
        {
            base=(base*base)%mod;
            p/=2;
        }
    }
    return res%mod;
}
