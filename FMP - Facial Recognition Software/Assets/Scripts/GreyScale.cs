using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GreyScale : MonoBehaviour {


    public Texture2D texture;
    public Texture2D texture2;
    public Color specs;
    public Color specs1;
    public Color specs2;
    public Color newSpecs;

    // Use this for initialization
    void Start () {

        int centrePoint = texture.width / 2;
        Vector2 DetectionWindow = new Vector2(360,720);

        for (int x = 0; x < texture.width; x++)
        {
            for (int y = 0; y < texture.height; y++)
            {
                if (x > (centrePoint-(DetectionWindow.x/2)) && x < (centrePoint + (DetectionWindow.x / 2)))
                {
                    specs = texture.GetPixel(x, y);
                    float avg = (specs.r + specs.g + specs.b) / 3.0f;
                    newSpecs = new Color(avg, avg, avg);
                }
                else
                {
                    newSpecs = Color.black;
                }
                texture.SetPixel(x, y, newSpecs);

            }
        }
        texture.Apply();
        GetComponent<SpriteRenderer>().sprite = Sprite.Create(texture, new Rect(0, 0, texture.width, texture.height), new Vector2(0.5f, 0.5f));

    }
     

    private void Update()
    {
    }

}
